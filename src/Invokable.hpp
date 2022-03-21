#ifndef RAYLIB_PLUSPLUS_INVOKABLE
#define RAYLIB_PLUSPLUS_INVOKABLE
    #include <functional>
    #include <type_traits>
    #include <vector>
    #include <algorithm>
    #include <mutex>

namespace raylib {
    namespace cpp {
#pragma region Placeholder Generator
        template<int>
        struct placeholder_template {};

        template<int N>
        struct std::is_placeholder<placeholder_template<N>> : std::integral_constant<int, N + 1> {};
#pragma endregion

        template<typename... A>
        class callback {
        private:
            size_t hash;
            std::function<void(A...)> func;

            template<typename T, class _Fx, std::size_t... Is>
            void create(T* obj, _Fx&& func, std::integer_sequence<std::size_t, Is...>) {
                this->func = std::function<void(A...)>(std::bind(func, obj, placeholder_template<Is>...));
            }

            template<class _Fx, std::size_t... Is>
            void create(_Fx&& func, std::integer_sequence<std::size_t, Is...>) {
                this->func = std::function<void(A...)>(std::bind(func, placeholder_template<Is>...));
            }

        public:
            const inline bool operator == (const callback& cb) { return (hash == cb.hash); };
            const inline bool operator != (const callback& cb) { return (hash != cb.hash); };

            template<typename T, class _Fx>
            callback(T* obj, _Fx&& func) {
                hash = static_cast<size_t>(&this->func) ^ (&typeid(callback<A...>))->hash_code();
                create(obj, func, std::make_integer_sequence<std::size_t, sizeof...(A)> {});
            }

            template<class _Fx>
            callback(_Fx&& func) {
                hash = static_cast<size_t>(&this->func) ^ (&typeid(callback<A...>))->hash_code();
                create(func, std::make_integer_sequence<std::size_t, sizeof...(A)> {});
            }

            const inline callback& operator () (A... args) {
                func(args...);
                return (*this);
            }

            void invoke(A... args) { func(args...); }

            constexpr size_t hash_code() const throw() { return hash; }

            callback<A...> clone() { return callback<A...>(func); }
        };

        template<typename... A>
        class invokable {
        private:
            std::mutex safety_lock;
            std::vector<callback<A...>> callbacks;

        public:
            const inline invokable& operator += (const callback<A...>& cb) { return hook(cb); };
            const inline invokable& operator -= (const callback<A...>& cb) { return unhook(); };
            const inline invokable& operator = (const callback<A...>& cb) { return hook_unhook(cb); };
            const inline invokable& operator () (A... args) { return invoke(args...); };

            invokable& hook(callback<A...> cb) {
                std::lock_guard<std::mutex> g(safety_lock);

                if (std::find(callbacks.begin(), callbacks.end(), cb) == callbacks.end())
                    callbacks.push_back(cb);

                return (*this);
            }

            invokable& unhook(callback<A...> cb) {
                std::lock_guard<std::mutex> g(safety_lock);

                typename std::vector<callback<A...>>::iterator it;
                it = std::find(callbacks.begin(), callbacks.end(), cb);

                if (it != callbacks.end())
                    callbacks.erase(it);

                return (*this);
            }

            invokable& hook_unhook(callback<A...> cb) {
                std::lock_guard<std::mutex> g(safety_lock);

                callbacks.clear();
                (*this) += cb;

                return (*this);
            }

            invokable& unhook_all() {
                std::lock_guard<std::mutex> g(safety_lock);

                callbacks.clear();
                return (*this);
            }

            invokable& invoke(A... args) {
                std::lock_guard<std::mutex> g(safety_lock);

                for (size_t i = 0; i < callbacks.size(); i++)
                    callbacks[i](args...);

                return (*this);
            }
        };
    }
}
#endif
