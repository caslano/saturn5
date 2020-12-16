// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an unordered associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/associative_container_adaptor.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator,
    class LocalIterator, class ConstLocalIterator,
    class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class LocalIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter,
    class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct unordered_associative_container_adaptor_base
{

    typedef associative_container_adaptor
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter   , ValueFromBaseConverter,
        KeyToBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_<
                ::boost::mpl::is_na<LocalIteratorFromBaseConverter>,
            // {
                    detail::iterator_from_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::local_iterator,
                        LocalIterator,
                        BOOST_DEDUCED_TYPENAME Base::const_local_iterator,
                        ConstLocalIterator
                    >,
            // }
            // else
            // {
                    LocalIteratorFromBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief Container adaptor to build a type that is compliant to the concept of an unordered associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class LocalIterator,
    class ConstLocalIterator,

    class KeyType,

    class IteratorToBaseConverter        = ::boost::mpl::na,
    class IteratorFromBaseConverter      = ::boost::mpl::na,
    class LocalIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter           = ::boost::mpl::na,
    class ValueFromBaseConverter         = ::boost::mpl::na,
    class KeyToBaseConverter             = ::boost::mpl::na,

    class FunctorsFromDerivedClasses     = mpl::vector<>

>
class unordered_associative_container_adaptor :

    public unordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        LocalIterator, ConstLocalIterator,
        KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type
{
    typedef BOOST_DEDUCED_TYPENAME unordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        LocalIterator, ConstLocalIterator,
        KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // Metadata ---------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Base::key_equal key_equal;
    typedef BOOST_DEDUCED_TYPENAME Base::hasher hasher;

    typedef LocalIterator      local_iterator;
    typedef ConstLocalIterator const_local_iterator;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::mpl::is_na<LocalIteratorFromBaseConverter>,
        // {
                detail::iterator_from_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::local_iterator,
                    local_iterator,
                    BOOST_DEDUCED_TYPENAME Base::const_local_iterator,
                    const_local_iterator
                >,
        // }
        // else
        // {
                LocalIteratorFromBaseConverter
        // }

        >::type local_iterator_from_base;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef unordered_associative_container_adaptor
                unordered_associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    // bucket interface:

    BOOST_DEDUCED_TYPENAME base_::size_type bucket_count() const
    {
        return this->base().bucket_count();
    }

    BOOST_DEDUCED_TYPENAME base_::size_type max_bucket_count() const
    {
        return this->base().max_bucket_count();
    }

    BOOST_DEDUCED_TYPENAME base_::size_type bucket_size(
        BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->base().bucket_size(n);
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type bucket(
        const CompatibleKey & k) const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::key_to_base key_to_base;
        return this->base().bucket(
            this->template functor<key_to_base>()(k)
        );
    }

    local_iterator       begin(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().begin(n) );
    }

    const_local_iterator begin(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().begin(n) );
    }

    local_iterator       end(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().end(n) );
    }

    const_local_iterator end(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().end(n) );
    }

    // hash policy

    float load_factor() const
    {
        return this->base().load_factor();
    }

    float max_load_factor() const
    {
        return this->base().max_load_factor();
    }

    void max_load_factor(float z)
    {
        return this->base().max_load_factor(z);
    }

    void rehash(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->base().rehash(n);
    }

    // We have redefined end and begin so we have to manually route the old ones

    BOOST_DEDUCED_TYPENAME base_::iterator begin()
    {
        return base_::container_adaptor_::begin();
    }

    BOOST_DEDUCED_TYPENAME base_::iterator end()
    {
        return base_::container_adaptor_::end();
    }

    BOOST_DEDUCED_TYPENAME base_::const_iterator begin() const
    {
        return base_::container_adaptor_::begin();
    }

    BOOST_DEDUCED_TYPENAME base_::const_iterator end() const
    {
        return base_::container_adaptor_::end();
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

/* unordered_associative_container_adaptor.hpp
PEQ4E5UfkxS+8+BFcIrS6Xx4FSyG18Fp7jqp+iTwWp910hnyv1z+V8j/Svk/W/7Plf/z5P985VMtvCOJduJraY1aKw19czCWddJ5iPh10+RTwt9sFMCtm/3XUecdYC212VCIGMDvwqGNX1d9it8fIAadir+ID1BbDkfw0p6MCK23rkEev+b6mNZd34SR7z2SC6NrsL0LE6/DrvFZi93G752I/a8nO8vxN35tdi1qtj47DBE6UxVOQkTWandu9v8+ZA16mxAb+f089Fu/3YLbZfy+FLERsR2xV+u5T6HXrB/pO7zhdd3ew6Nru4X8LkN413iXI4+s817P7zsQkfXe7cOja77JF+HfvYQF9QEjDrz++4FnDbgHjKwD18DrEVsQ8WvCez/n9yfzUFuD2IR4CuG3VuyM0nox8ejA70GIUsRKxIa49eMtyPfDXSEi4teSW42OricP4Xcxok7rytfDTYi1Ib3zM5xixFLE9YgtiB2IfYis4gynd3HTmnPT0/Q0Pf97zxe0/38+pg/5+//Q/f6D6Zjn2/3/CoPNmIV2F4Tv9x/k+T6gh/YGpCuuaYhy7Gclu/vQz8aRiRPHhud6ZCzhHf79NY+3Vfvbzw2Gx6RDoZ078Fl6yF0C1IhzB8zsySafhPxMk+cFE5xDIPPHOzma/x9u8q2BLc7fnVytAXxsatMDvZ0kVFPrf+uvub5BZu7YoOb65HYPM98Oz+h91zoyfy76XzL9IObtbAAezUdqzm2s6f8joLMRNWcXnSs8y/RTgq77dm4A+iTtUmTDTL9rMCc650dRmu/OT1bhxigz0z6Y6bpRZXrnoXeu6aUHZzF/1xadd7PCYm/76O8rchm7E/btWWHxKGIyakMQTyMKESH5k1kmzGwxfBU3Lka9ZauIaMy8YEp2OC+cAqrGfMddw6h//kOlz/kPNd6zD2R3KSTeOuMgdq1jktY0f0C5PAreCkPnYPb9R6Q8Nu4czLD5gZIHnM3BDORtbE6WcWTC8zEJBOUtvB9FeyPk1uVJE50+SSH7jNfjz840s0Wuvze5Zrf5nFORo7I0We6u4b/mnmW/hxNXPt299UdZ2GqD04PNPWV8UXgfgcr4kWbm4uDsYGvbL9/bzNTa2sZ2fl1ifhQn9UmK+1ZH89tt4TlmZnXSCtq0F4IzsYs6Ks+a+gPBbGeM1YEHLYxV86uxnKP6P8HMXJW0lrqb6bo/28lV+b/c9HsljcXtKwIrAzmmHnU7xTnPU7/qwnsaVD/aWNwuCBYH8zxxW2j5ynjZmyZhe6rXadgjTMFVuL6YukWw3fpTrHrlrV+vtA/XnScQpyD3/t6BUJ0z0YtG7BfwJgT65t7F8CMo4e4pWdvQnhLqWrdgeB9IeW2t1RXKar3zU7cmOD91m8/5qdvjz1+RGumGWq3JiyTHnu032B4IzxV8syD2XbFXdTNf+9PaI07AzO6kjEjdnMVeg4WVic9mwWzs3rSf5jZ+b5obD73D+ihcdXopZspShsK1Q+HSFohEYZK5zAO+N0PhSPcJh9oum9Sx8PAOzYMVcD3hyE+OhKNx59eYed7GuXrHjTT5uGAtM7iZwVy9+wLOj0z9hIbOuZFbnd36c1pITt29jRpR7+wb+Xd2anS/XZHrRmlwGnu9QvWMPfLx5+KY2fGu2Slm1qdtpt1DnhIys9azZiZ7WjOjjtQ/w0ht2ydmbl7A5KTBjSbv4brVN84t5sndtjRdbWmkTfiqmXsucL7tERienavMPtXUJ5KHqPGLR/58FjjXVgrrAtF3d63b7p1iZiYFv0+7F9+u5qjtG21mRgW/zTd29foQSp+hlv7dJY/E8VhKqGvefR+sNL23Al9i1WECdQo=
*/