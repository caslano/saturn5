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
EkaJoKRSciiFlCLKUUoppZxSQammtFHaKTcoDylDlHHKBAVNpVBZVA6VRzWg2lLFVEeqFzWcGk9Npm6gZlC3UrOpe6kF1CLqEepxahm1mlpHbaLepz6hDlMnqFgaicag8WlGNFuaG82d5kcLoAXTwmnRtDRaOi2Tlk8rpB2hHaWV0OppDbQ2WiftPm2INkIbp5EVmYosRa6iQNFA0VTRWlGi6K7orRigGKsYr5ismKKYpZireFyxXLFCsUqxVrFOsUWxTbFHcUIRTyfT1eh8uhHdmu5Cd6MvoHvSfekr6GH0cHokfQM9jb6VvpOeTd9LL6AfoB+nV9Pr6R30G/Qe+gB9kD5MH6NP0jWUOEpCJXMlkZKb0iIlP6UIpWilWKVEpUylPKUDSoVKZUqVSjVKzUodSn1K95WwDBKDxlBhsBg8hoBhwLBmiBkShgtjASOAEcoIY0QwUhipjHRGFiObkcvIZ1Qwqhl1jAZGC6OTMcrAKxOUKcp0ZYaymrKGMk/ZXNlWWazspuyp7KMcrhypHK2cqLxXOVf5gHKx8nHlCuUa5XrlVuV25RvKXcq9yveUB5QHlUeVx5QJKhQVrgpfxVxForJCJVglSWWDSqZKjkq+ygGVIyrlKlUqtSpNKs0qHSq9Kg9VhlVGVCZV8Kp0Vaaqpaq1qkjVRXWB6iJVH9Uw1VjVJNUU1VTVDNUs1XzVAtWjqqWq5apVqnWqjaptqp2qN1R7VO+pDqiOqE6oMtQ01EzVzNXc1Baoean5qyWrpantVctVy1MrUitWK1ErU6tQa1RrVetSG1SbUEOrY9Vp6irqHHWuupG6UN1S3VF9kbqXerh6hPoG9RT1rerb1feqH1UvUS9VL1OvUm9Sb1XvUO9U71MfVh9Xn1THanA1eBpCDVMNaw2RhkTDXcNTw0fDTyNUI0IjXiNVI10jW6NA46hGrUaDRptGp8YNjSGNUQ2CJl1TTZOvaaBppGmuKdZ00/TQ9NT00YzXTNPcqZmpmadZpHlEs0KzUrNJs1dzWHNMk8DUYHKYXKYl05bpyJQwPZjezBXMYGY4M5aZyNzATGFuZW5n5jDzmAeYR5hHmeXMSmYDs5PZxexljjDHmEgtvBZJi66losXTMtASaom1Fmgt0vLUitSK1dqulaWVo1WoVapVrVWn1aDVqNWs1a3VpzWkNao1oYVkkVkUlgbLlrWA5cHyYoWxElkbWBmsbFYuK49VwDrCOs6qYFWz2lm9rPusAdYwa5JFY2uwmWw+e+q3v+Zsd/Yithc7gB3MDmWHs5PYKezt7EJ2CbuMXcWuZzew+9j32YPsIfY4e5JN5tA5lhwJZwHHk+PH8ecEcOI5KZwMTg4nl1PIOc4p51Rw6jiNnE5ON+ce5yHnCWeEM85BaxO0Kdoa2hxtnraBtqm2rbaHtqd2sHaYdrx2onaqdob2Vu1s7QLtA9pF2pXaNdpd2r3a97QHtUe10VwCl8TlcwVcIdeca8l143pxvbl+3GBuBDedm8XN4R7llnLLuLXcBm4Tt4Pbze3jDnGHuWNcrA5JR0VHTUegI9aR6LjoLNIJ0AnTidBJ1knRSdXJ0MnXKdQ5rlOhU63ToNOs06LTqXNDp1unR2dEZ1RnXAfJw/PoPDUen2fKE/NceB48T148L42XydvLy+UV8A7wSnhlvBpeC6+Vd4PXyxvljfGwuiRdii5Dl68r0LXUFek66nroeuv66YbqhutG627QTdNN183Szdc9oFuqW65br9uk26zbodutO6Q7oqvCV+Nb8q35i/jefB9+AD+CH8mP5yfxU/k5/Hx+Af8o/zi/nF/Fr+M38Nv4ffwhPloPr0fWo+tp6LH0OHqmemI9R70=
*/