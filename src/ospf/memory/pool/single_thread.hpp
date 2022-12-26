#pragma once

#include <ospf/memory/pool/concept.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace pool
        {
            template<typename T, typename Pool>
            class ObjectPool<T, Pool, off>
            {
            public:
                struct Deleter
                {
                    Deleter(const Pool& p)
                        : pool(p) {}
                    Deleter(const Deleter& ano) = default;
                    Deleter(Deleter&& ano) noexcept = default;
                    Deleter& operator=(const Deleter& rhs) = default;
                    Deleter& operator=(Deleter&& rhs) noexcept = default;
                    ~Deleter(void) noexcept = default;

                    inline void operator()(PtrType<T> ptr) const noexcept
                    {
                        pool->destory(ptr);
                    }

                    mutable Ref<Pool> pool;
                };

                template<typename U>
                    requires std::is_convertible_v<PtrType<T>, PtrType<U>>
                struct BaseDeleter
                {
                    BaseDeleter(const Pool& p)
                        : pool(p) {}
                    BaseDeleter(const BaseDeleter& ano) = default;
                    BaseDeleter(Deleter&& ano) noexcept = default;
                    BaseDeleter& operator=(const BaseDeleter& rhs) = default;
                    BaseDeleter& operator=(BaseDeleter&& rhs) noexcept = default;
                    ~BaseDeleter(void) noexcept = default;

                    inline void operator()(PtrType<U> ptr) const noexcept
                    {
                        auto temp = static_cast<PtrType<T>>(ptr);
                        assert(temp != nullptr);
                        pool->destory(temp);
                    }

                    mutable Ref<Pool> pool;
                };

            public:
                ObjectPool(void) = default;
                ObjectPool(const ObjectPool& ano) = delete;
                ObjectPool(ObjectPool&& ano) noexcept = default;
                ObjectPool& operator=(const ObjectPool& rhs) = delete;
                ObjectPool& operator=(ObjectPool&& rhs) noexcept = default;
                ~ObjectPool(void) noexcept = default;

            public:
                template<typename... Args>
                    requires std::is_constructible_v<T, Args...>
                inline Ptr<T> make_ptr(Args&&... args) noexcept
                {
                    return make_ptr_from_pool<pointer::PointerCategory::Raw>(std::forward<Args>(args)...);
                }

                template<typename U, typename... Args>
                    requires std::is_convertible_v<PtrType<T>, PtrType<U>> && std::is_constructible_v<T, Args...>
                inline Ptr<U> make_base_ptr(Args&&... args) noexcept
                {
                    return make_base_ptr_from_pool<U, pointer::PointerCategory::Raw>(std::forward<Args>(args)...);
                }

                template<typename... Args>
                    requires std::is_constructible_v<T, Args...>
                inline Unique<T> make_unique(Args&&... args) noexcept
                {
                    return make_ptr_from_pool<pointer::PointerCategory::Unique>(std::forward<Args>(args)...);
                }

                template<typename U, typename... Args>
                    requires std::is_convertible_v<PtrType<T>, PtrType<U>> && std::is_constructible_v<T, Args...>
                inline Unique<U> make_base_unique(Args&&... args) noexcept
                {
                    return make_base_ptr_from_pool<U, pointer::PointerCategory::Unique>(std::forward<Args>(args)...);
                }

                template<typename... Args>
                    requires std::is_constructible_v<T, Args...>
                inline Shared<T> make_shared(Args&&... args) noexcept
                {
                    return make_ptr_from_pool<pointer::PointerCategory::Shared>(std::forward<Args>(args)...);
                }

                template<typename U, typename... Args>
                    requires std::is_convertible_v<PtrType<T>, PtrType<U>>&& std::is_constructible_v<T, Args...>
                inline Shared<U> make_base_shared(Args&&... args) noexcept
                {
                    return make_base_ptr_from_pool<U, pointer::PointerCategory::Shared>(std::forward<Args>(args)...);
                }

            public:
                inline decltype(auto) deleter(void) const noexcept
                {
                    return Deleter{ _pool };
                }

                template<typename U>
                    requires std::is_convertible_v<PtrType<U>, PtrType<T>>
                inline decltype(auto) base_deleter(void) const noexcept
                {
                    return BaseDeleter<U>{ _pool };
                }

            private:
                template<pointer::PointerCategory category, typename... Args>
                inline decltype(auto) make_ptr_from_pool(Args&&... args) noexcept
                {
                    auto ptr = _pool.malloc();
                    if (ptr == nullptr)
                    {
                        return pointer::Ptr<T, category>{};
                    }
                    else
                    {
                        if constexpr (category == pointer::PointerCategory::Raw)
                        {
                            return pointer::Ptr<T, category>{ ::new (ptr) T(std::forward<Args>(args)...) };
                        }
                        else
                        {
                            return pointer::Ptr<T, category>{ ::new (ptr) T(std::forward<Args>(args)...), deleter() };
                        }
                    }
                }

                template<typename U, pointer::PointerCategory category, typename... Args>
                    requires std::is_convertible_v<PtrType<T>, PtrType<U>>
                inline decltype(auto) make_base_ptr_from_pool(Args&&... args) noexcept
                {
                    auto ptr = _pool.malloc();
                    if (ptr == nullptr)
                    {
                        return pointer::Ptr<U, category>{};
                    }
                    else
                    {
                        if constexpr (category == pointer::PointerCategory::Raw)
                        {
                            return pointer::Ptr<U, category>{ static_cast<PtrType<U>>(::new (ptr) T(std::forward<Args>(args)...)) };
                        }
                        else
                        {
                            return pointer::Ptr<U, category>{ static_cast<PtrType<U>>(::new (ptr) T(std::forward<Args>(args)...)), base_deleter<U>() };
                        }
                    }
                }

            private:
                Pool _pool;
            };
        };
    };
};
