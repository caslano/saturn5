/*-----------------------------------------------------------------------------+
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_ITERATOR_HPP_JOFA_091003
#define BOOST_ICL_ITERATOR_HPP_JOFA_091003

#include <iterator>
#include <boost/config/warning_disable.hpp>

namespace boost{namespace icl
{

/** \brief Performes an addition using a container's memberfunction add, when operator= is called. */
template<class ContainerT> class add_iterator
{
public:
    /// The container's type.
    typedef ContainerT container_type;
    typedef std::output_iterator_tag iterator_category; 
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    /** An add_iterator is constructed with a container and a position 
        that has to be maintained. */
    add_iterator(ContainerT& cont, typename ContainerT::iterator iter)
    : _cont(&cont), _iter(iter) {}

    /** This assignment operator adds the \c value before the current position.
        It maintains it's position by incrementing after addition.    */
    add_iterator& operator=(typename ContainerT::const_reference value)
    {
        _iter = icl::add(*_cont, _iter, value);
        if(_iter != _cont->end())
            ++_iter;
        return *this;
    }

    add_iterator& operator*()    { return *this; }
    add_iterator& operator++()   { return *this; }
    add_iterator& operator++(int){ return *this; }

private:
    ContainerT*                   _cont;
    typename ContainerT::iterator _iter;
};


/** Function adder creates and initializes an add_iterator */
template<class ContainerT, typename IteratorT>
inline add_iterator<ContainerT> adder(ContainerT& cont, IteratorT iter_)
{
    return add_iterator<ContainerT>(cont, typename ContainerT::iterator(iter_));
}

/** \brief Performes an insertion using a container's memberfunction add, when operator= is called. */
template<class ContainerT> class insert_iterator
{
public:
    /// The container's type.
    typedef ContainerT container_type;
    typedef std::output_iterator_tag iterator_category; 
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    /** An insert_iterator is constructed with a container and a position 
        that has to be maintained. */
    insert_iterator(ContainerT& cont, typename ContainerT::iterator iter)
    : _cont(&cont), _iter(iter) {}

    /** This assignment operator adds the \c value before the current position.
        It maintains it's position by incrementing after addition.    */
    insert_iterator& operator=(typename ContainerT::const_reference value)
    {
        _iter = _cont->insert(_iter, value);
        if(_iter != _cont->end())
            ++_iter;
        return *this;
    }

    insert_iterator& operator*()    { return *this; }
    insert_iterator& operator++()   { return *this; }
    insert_iterator& operator++(int){ return *this; }

private:
    ContainerT*                   _cont;
    typename ContainerT::iterator _iter;
};


/** Function inserter creates and initializes an insert_iterator */
template<class ContainerT, typename IteratorT>
inline insert_iterator<ContainerT> inserter(ContainerT& cont, IteratorT iter_)
{
    return insert_iterator<ContainerT>(cont, typename ContainerT::iterator(iter_));
}

}} // namespace icl boost

#endif // BOOST_ICL_ITERATOR_HPP_JOFA_091003



/* iterator.hpp
+36ltZOfreHj4C2TRSxEIw9/6deB4RPPRf2LnELbgPn5hf2/iH3A0trJpzFJ9gRpTJBdQqrDyV3rcZ7oxPCJ51u53pfKtqBon7CoLWjRvmBp7eST/UpVHbKTsS/cvAAxKMOJzp0ZPvGc7BJSHch+rCow28Xcdjyzl051wL5ZWjv5NBYV9xOZ/2cVH87s2aL2oUE8D2H6XkVsI7JKgB77iDlaNhLf0Tz56gn3c5ECSpWPiSeirwvRzwTOB/ewDnevsDqc3b8NpvzUjeETz1U6KH/FfmxeRhqrQx6rwyPR1wavQw752yD/1w+TkAe8DneuMPuJ0wZ1Z/jEc009GNLH2ZauFPURX+QwvcgAPj5VNnuZfXY+R9K88O71c7WfDa064LrF/Aik3GTzkeL+NVaHixEhbO0ifOK5pi1IphOUQXXgOkFcT0ucI7IZz98z/wXieKS1QpybuF8JzTqQD4Enoi8DBatDEvP5QX14pksvhv9XeK7lQ+FNBpv/33E/H7R2q+qgfP6AzYNkx1WUBdbhQRJcPhaGe4c+Omsz2ShVdbwPH8R5QOz/3Ea+2j49t5Ov9uOQLvKBbPazOmCfpPWK1uZnDzgf7nA+3GDrjPvP/YrBB24PXjUPiPbx1XVQKtT26QvXCNFev1iHZ2r/BVSHXF4H8gdDe4irMUfg99H9i8fndYACFR/eifNyXq64RpFfD+Vb7i9AznwtaPpP
*/