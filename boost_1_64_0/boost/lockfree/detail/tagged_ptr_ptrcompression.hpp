//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2009, 2016 Tim Blechmann, based on code by Cory Nelson
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_PTRCOMPRESSION_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_PTRCOMPRESSION_HPP_INCLUDED

#include <cstddef>              /* for std::size_t */
#include <limits>

#include <boost/cstdint.hpp>
#include <boost/predef.h>

namespace boost {
namespace lockfree {
namespace detail {

#if BOOST_ARCH_X86_64 || defined (__aarch64__)

template <class T>
class tagged_ptr
{
    typedef boost::uint64_t compressed_ptr_t;

public:
    typedef boost::uint16_t tag_t;

private:
    union cast_unit
    {
        compressed_ptr_t value;
        tag_t tag[4];
    };

    static const int tag_index = 3;
    static const compressed_ptr_t ptr_mask = 0xffffffffffffUL; //(1L<<48L)-1;

    static T* extract_ptr(volatile compressed_ptr_t const & i)
    {
        return (T*)(i & ptr_mask);
    }

    static tag_t extract_tag(volatile compressed_ptr_t const & i)
    {
        cast_unit cu;
        cu.value = i;
        return cu.tag[tag_index];
    }

    static compressed_ptr_t pack_ptr(T * ptr, tag_t tag)
    {
        cast_unit ret;
        ret.value = compressed_ptr_t(ptr);
        ret.tag[tag_index] = tag;
        return ret.value;
    }

public:
    /** uninitialized constructor */
    tagged_ptr(void) BOOST_NOEXCEPT//: ptr(0), tag(0)
    {}

    /** copy constructor */
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_ptr(tagged_ptr const & p):
        ptr(p.ptr)
    {}
#else
    tagged_ptr(tagged_ptr const & p) = default;
#endif

    explicit tagged_ptr(T * p, tag_t t = 0):
        ptr(pack_ptr(p, t))
    {}

    /** unsafe set operation */
    /* @{ */
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_ptr & operator= (tagged_ptr const & p)
    {
         ptr = p.ptr;
         return *this;
    }
#else
    tagged_ptr & operator= (tagged_ptr const & p) = default;
#endif

    void set(T * p, tag_t t)
    {
        ptr = pack_ptr(p, t);
    }
    /* @} */

    /** comparing semantics */
    /* @{ */
    bool operator== (volatile tagged_ptr const & p) const
    {
        return (ptr == p.ptr);
    }

    bool operator!= (volatile tagged_ptr const & p) const
    {
        return !operator==(p);
    }
    /* @} */

    /** pointer access */
    /* @{ */
    T * get_ptr() const
    {
        return extract_ptr(ptr);
    }

    void set_ptr(T * p)
    {
        tag_t tag = get_tag();
        ptr = pack_ptr(p, tag);
    }
    /* @} */

    /** tag access */
    /* @{ */
    tag_t get_tag() const
    {
        return extract_tag(ptr);
    }

    tag_t get_next_tag() const
    {
        tag_t next = (get_tag() + 1u) & (std::numeric_limits<tag_t>::max)();
        return next;
    }

    void set_tag(tag_t t)
    {
        T * p = get_ptr();
        ptr = pack_ptr(p, t);
    }
    /* @} */

    /** smart pointer support  */
    /* @{ */
    T & operator*() const
    {
        return *get_ptr();
    }

    T * operator->() const
    {
        return get_ptr();
    }

    operator bool(void) const
    {
        return get_ptr() != 0;
    }
    /* @} */

protected:
    compressed_ptr_t ptr;
};
#else
#error unsupported platform
#endif

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_TAGGED_PTR_PTRCOMPRESSION_HPP_INCLUDED */

/* tagged_ptr_ptrcompression.hpp
zHuYWzzG73TkHh5H21dWivBo3Y/f4E4oVLle7hNjrYK/5Moyj9fUvunwhlBGDR3rtdWjbr7JXhMUQ72s5/JfxuxobhvRhavjN0+qnpZ8aBJULqRDymHQxf58L5ByKNTnwXX3YVnPcai0kUMwY/Fz4uLgcshdYq67P1P+qHnUU2zOb8LS9TVx5yjX9WtMKW7kcmt8NiH/fLYd+RaLeT315HnillOnjHWpL3tgS9q2S/s/rDQobdLyh277z1P+bzCkTcLiT7XV5OWmeL8uh28kbX9XWn4m4qWtpoxDt/vrVDizqtt9wtofL+1+y/Da/X2JflP5reSput2fURrc7l9bqtv9IP3Ep+sHhxuDqY+fxLLg/J2fV57Gg5yfPQ/tpjDXHU4sO+m3dOND9ROdcSxJqBnHeOLYxhRHrYIVXhzbnGIcA/3UxAbmfEwzxdFW0wozfmmnKX77DPFrlI7sm+JXlpeXG2YZDzt5/EaEU8bTGtaM3034zagZv8zssqKzM/MXZ88PM44ZpymOFY38nntLXZSOeZZ6IMsQR/2ohBlHwtDfDtZTfVgdgqm9wr+xz2vs34pfvY8xbRa6bOF/z+3Mj2Rpq4gjdjqOpr6EM+8Y7dYc317BSZUp75aULs1TSwyHHtvuKKt1bEu40l7p/Cwx5KPJX7YhD03+csx7X5eFv0ZsVdnpGVM3DCoTzqUsONf9vkR9nhNyPdjflul+XlDZxTY1l93RWsquxApddm+fpOyOhll2R8Msu6Nhlt3ROpTd0f+wsmtUbi67e5qa69U25aHKrii7MC+8OqtN+Unr1bDaptXN3PIl3/kb4pibN5+eXmjZ6lNeq2wR5ukqtwGNMyXPF7nyvE1SzTzvhZ8SQ3oKi4tIVHZ5dpjtRMnJ83xEOHmekRyc52nSlq0zxNHuroTb5+N657sUfqmrTc8vfsNvw9aVh9eGhZMPTZzPnMQvVPs1XvLLal6zTBMo04OG/FKjAnoA9nf4ZQXFRZn2cv5h5t/BUyzfgAzuMMQ30V5bxRBfu7tnf7oUbl/lyCnGcbTEcWMLv+cuclFnee6PuuJoWuDDEFf9rerb6vr2yE20xfjf3Ma46oG41t9Olux6wLdE6gHXu+sOZ0je+4ELv/HTZklw+grzyhcU52YWh7ufS5slJ83/8eGsUZKR4vf8kvRnX8QstMcsrvjxtlLFa7ga89qxrV7jo6/y+6zVkv+DbFfM06HWVpF4yxi9xtoy65X7BlVmazHdKJs4x7uYXcIfitlnmzDHyfb3E68tqfn9hJ2mJJUmWRNfynKxqyxbnqnrS+WeJrI6bGlwXqnaJFN92yRlaXgXoa45y5RHhBcsl3uafLt+up2WhUvN7VOflrqdVUc3zGG77nelxfXISbnVfN42qus61fa8EXb4c03rXHkQX4dnc2/Xk8813Sn5UujKlxat/AEmSMD1MRPxc9CVL2WGMSj3rb1eX+reZ0JdbEo/fk/6fJ80zWotKbmHM43Pp9bsa23k5Ig7jYZxGPdx9bcIb2nt/S3Cde7DYe7LG/wZ+/Imf+a+PP7C78sfWfrt+4TkSY2+/CpXX55zZ1+e89r78t+IfBa55LOijaWOnpa0m1J2ictCl12JFbrsmtnXEUqquewIN7yyS1wWXtklLguv7BKXhV92icv+s8pu8DJz2ZW3NdctGeayk3FYeHULYbjqlqKCXHPdit/TVbdwD9c7njnt/QE8JwH9DlNCGrMMadSvaWvKp16L7Ap13V5rBP8XYb5v7lcQvrw703uT6dCNeSD+Zf5Qj1H0/OF+5d6GVR3ijHKs76ev1+/BdBivKj/tCKO+ScZ1GD2R23gltzK3JPNKTydWczqs39o=
*/