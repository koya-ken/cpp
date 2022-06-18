#include <vector>
#include <memory>
#include <iostream>
#include <memory_resource>

using Vecf = std::pmr::vector<float>;
using Vecf2 = std::vector<float>;
using MemoryPool = std::pmr::synchronized_pool_resource;

// https://techblog.altplus.co.jp/entry/2017/12/17/000000
// template<std::size_t N>
class stack_memory_resource : public std::pmr::memory_resource
{
    MemoryPool pool;

public:
    stack_memory_resource() noexcept : pool() {}
    stack_memory_resource(stack_memory_resource const &) = delete;
    stack_memory_resource &operator=(stack_memory_resource const &) = delete;

protected:
    void *do_allocate(std::size_t bytes, std::size_t alignment) override
    {
        std::cout << "do_allocate(" << bytes << "," << alignment << ")" << std::endl;
        return this->pool.allocate(bytes, alignment);
    }
    void do_deallocate(void *p, std::size_t bytes, std::size_t alignment) override
    {
        std::cout << "do_deallocate(" << p << "," << bytes << "," << alignment << ")" << std::endl;
        this->pool.deallocate(p, bytes, alignment);
    }
    bool do_is_equal(std::pmr::memory_resource const &other) const noexcept override
    {
        std::cout << "do_is_equal(" << &other << ")" << std::endl;
        return this->pool.is_equal(other);
    }
};

void main2()
{
    const int max = 100;
    std::shared_ptr<Vecf2> cache[max] = {};
    for (size_t i = 0; i < max; i++)
    {
        auto vec = std::make_shared<Vecf2>();
        cache[i] = vec;
        vec->reserve(100);
        std::cout << i << "," << vec << std::endl;
    }
    for (size_t i = 0; i < max; i++)
    {
        cache[i] = nullptr;
    }
    for (size_t i = 0; i < max; i++)
    {
        auto vec = std::make_shared<Vecf2>();
        cache[i] = vec;
        vec->reserve(100);
        std::cout << i << "," << vec << std::endl;
    }
}

void main()
{
    const int max = 100;
    // MemoryPool mem_res;
    stack_memory_resource mem_res;
    std::shared_ptr<Vecf> cache[max] = {};
    for (size_t i = 0; i < max; i++)
    {
        auto vec = std::make_shared<Vecf>(&mem_res);
        cache[i] = vec;
        vec->reserve(100);
        // std::cout << i << "," << vec << std::endl;
    }
    for (size_t i = 0; i < max; i++)
    {
        cache[i] = nullptr;
    }
    for (size_t i = 0; i < max; i++)
    {
        auto vec = std::make_shared<Vecf>(&mem_res);
        cache[i] = vec;
        vec->reserve(100);
        // std::cout << i << "," << vec << std::endl;
    }
}