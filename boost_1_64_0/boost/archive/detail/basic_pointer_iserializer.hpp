#ifndef BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_pointer_oserializer.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/basic_serializer.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

// forward declarations
namespace archive {
namespace detail {

class basic_iarchive;
class basic_iserializer;

class BOOST_SYMBOL_VISIBLE basic_pointer_iserializer
    : public basic_serializer {
protected:
    explicit BOOST_ARCHIVE_DECL basic_pointer_iserializer(
        const boost::serialization::extended_type_info & type_
    );
    virtual BOOST_ARCHIVE_DECL ~basic_pointer_iserializer();
public:
    virtual void * heap_allocation() const = 0;
    virtual const basic_iserializer & get_basic_serializer() const = 0;
    virtual void load_object_ptr(
        basic_iarchive & ar,
        void * x,
        const unsigned int file_version
    ) const = 0;
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP

/* basic_pointer_iserializer.hpp
09Ot9/fJT2b95Zx1bXtBq27jWpq6rrk8c+iyoSZXPM+dt7EbOuSc9cKG83a8WavccqV30PvM3gPX2OY/XFo7//uaDQHzvkx7MeHIxce5PdxsbGMvf7Kxr5Y6xSQqJTJa88Kv8syP4/tfvH8psbTVrsR3mdaCnFJ7C0SlrbKeHV7UY7L78zrNZ7Uo67pyXmLHuu8bCRt8jZ3/vvbbm81srrXRvP8euXGkc/dSu913/aNKcjebT9fMD8V1y10dNXVtbreaj7tOvOngEtNzQfspn6lphyYPenp2sOdX0dlG3Zz2hSQPu79thb+H7WFJ+O1OaQ+riSzLrVvUdFPire926ZLYRmXLm/vP3XzrAF907ra057oTVL1bH/f18ZrQs+5wkwu5u+9vSRg2YNEt/s9ern7mbT0vn9myZ8XZp8rdo0Vf1lWNnRAgd98vfDDvQla/1hF1kw+tUwiDP0yoVFndo1qfRwNrKD/1Gxq+vtxpL6/ce1uCB/hfcB693srExmzD3fqus2dsWbijTKds2dmRbh3lI1dTbbvUr2Pyqbmy+cZoK8HNjtMetUx13b3Xmu98t0NmdpfUs922n3RqfXJXw+xhJ+rlfzh/fM/hKibnjq96nBM4ZnKduXtDLp2+fT3P5br55RaHO5SKazfl2BDHzxNCWm7M394r66Pr7ve+P2tffjOff615q8az9rf49tBq4LcpFtZW0+cJpv3zy7P52872Eq04dH7Frqr9yx7cVnFA6fvi0AuWPktKna4se57vdmN2jX3Zs4NET1KcnGY0XHhn6sX8ls7ZFxu8GTjWW21ed7zz4i7UwH1HrzolHZ6wsO0d+9Zz5gXIKzys//q+RcT1oH9OuXq9wbnUmLPyYZ5nYjfWqlG6fqvvRy9MGj2n8dcPPd42ed8kyWmZY9sV00zP5HaPGVGwZuszTe9Z7WrIclUXMqfGzLydF7hzRN3JoUHVux8buPf4sYfm1Qc5lcm7y587+M3h7+GrTvIsVsTc22+9+8OFvW1LS6oObGxqtmnIudPbWs5POnPAs0r4xfteNaL3rnYpWBtgPZ9y2ZV01v/j0Zz1ydHRGir4x+n0qxMe/2PD51WDhq36HNT3UKfa4//x1fTBgMMmn+8+uyL5dGly9u2+y+ysy3dc+LDcISdB8PY+95LP3r8zqcdD5WFX3v/d/93/3X/cmbIroJmlsH5RwvXbGAkO+sOf3Nd+yLqKsffNYgQSqpEHRfYQaB35eyUplB2l3YPI7LkV0r8RJiT7YRkL9/BQb19+eGvED/c01707TncI7nSanvS3EbjvSwlihHgtzfA9qpJel0KJBaQS/H2fFirmG57ai6P/Rk9RTTHxhRqlkn0JrwVeZcTPPzpf0fzZ+dZ7dq9dnY5Ftfl6coGe3NSLY4ulrlfev9oWpfVL3j5UcvqlyeL/PpGU/jtEugW+eOy39yhx+oZvLZQ3ZddAdjHrBQplKWZ/u7oUIycxfh7x6bbD+kMZP3oY41sOp31Dx9RBCfIXG0WbGuSvOps/y91M/tLY86SNZPwC1g8dxepHsfoM9jrGsPnNNJ4/+ktxTB5LWE+xUVLY/3Jd0JLN7wE2v9mZbD7GMv6Bf7D5Y31qHJuv8Wx5sv4B4hs6vKdrR96poD++FhhCqbEKSL+TjqWbEu8/Zq9DBt/gOqqw+U/bw64fTWDLlfULWJ+ayJY76ztMYmXWjya+oSPk6/JLvv/dx1rRD9uHGeevFIvRi+n2OdNLRDbWolZ4lcCW6KlYkQezd9l4OBtCvjX+m4iG4UwIvkevsuEo4sSQ9ROHE6qVUkM9kx9KKcYKIPvxD+75DANI+gZqkg+jenJeY3rUJSXE0mUMXr0=
*/