/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_ASSOCIATOR_BASE_HPP_JOFA_110301
#define BOOST_ICL_CONCEPT_INTERVAL_ASSOCIATOR_BASE_HPP_JOFA_110301

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/interval_type_of.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Selection<IntervalSet|IntervalMap>
//==============================================================================
template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_discrete<typename domain_type_of<Type>::type> 
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    //CL typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    return object.find(icl::detail::unit_trail<interval_type>(key_val));
}

template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_continuous<typename domain_type_of<Type>::type> 
                            , has_dynamic_bounds<typename interval_type_of<Type>::type> 
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    //CL typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    return object.find(icl::singleton<interval_type>(key_val));
}

template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_continuous<typename domain_type_of<Type>::type> 
                            , is_static_right_open<typename interval_type_of<Type>::type> 
                            , boost::detail::is_incrementable<typename domain_type_of<Type>::type>
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    const_iterator first_collision = object.lower_bound(icl::detail::unit_trail<interval_type>(key_val));
    // A part of the unit_trail(key_value)-interval may be found in the container, that
    // does not contain key_value. Therefore we have to check for its existence:
    return (  first_collision == object.end() 
           || icl::contains(key_value<Type>(first_collision), key_val) ) 
            ? first_collision 
            : object.end();
}

template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_continuous<typename domain_type_of<Type>::type> 
                            , is_static_left_open<typename interval_type_of<Type>::type> 
                            , boost::detail::is_incrementable<typename domain_type_of<Type>::type>
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    const_iterator last_collision = object.upper_bound(icl::detail::unit_trail<interval_type>(key_val));
    if(last_collision != object.begin())
        --last_collision;
    // A part of the unit_trail(key_value)-interval may be found in the container, that
    // does not contain key_value. Therefore we have to check for its existence:
    return (  last_collision == object.end() 
           || icl::contains(key_value<Type>(last_collision), key_val) ) 
            ? last_collision 
            : object.end();
}

// NOTE: find(object, key) won't compile if key is of continuous type that does
// not implement in(de)crementation (e.g. std::string).

template<class Type> inline
typename enable_if< is_interval_container<Type>
                  , typename Type::const_iterator>::type
find(const Type& object, const typename interval_type_of<Type>::type& inter_val)
{
    return object.find(inter_val);
}

//==============================================================================
//= Morphisms
//==============================================================================
template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type&
join(Type& object)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    iterator it_ = object.begin();
    if(it_ == object.end()) 
        return object;

    iterator next_ = it_; next_++;

    while(next_ != object.end())
    {
        if( segmental::is_joinable<Type>(it_, next_) )
        {
            iterator fst_mem = it_;  // hold the first member
            
            // Go on while touching members are found
            it_++; next_++;
            while(     next_ != object.end()
                    && segmental::is_joinable<Type>(it_, next_) )
            { it_++; next_++; }

            // finally we arrive at the end of a sequence of joinable intervals
            // and it points to the last member of that sequence
            const_cast<interval_type&>(key_value<Type>(it_)) 
                = hull(key_value<Type>(it_), key_value<Type>(fst_mem));
            object.erase(fst_mem, it_);

            it_++; next_=it_; 
            if(next_!=object.end())
                next_++;
        }
        else { it_++; next_++; }
    }
    return object;
}

}} // namespace boost icl

#endif



/* interval_associator_base.hpp
2fBdLPHFn1gzl8iaffYmBQR/QJ0SlwsPWtekOh1fFGNufEGNpt4XVo4+TQZrCIus9CZtPtaVrq4bRndvNRdaDZxBCZTIfrfcRC/9fqSYMWYrbfiwPXtcvx8tmthAGPbkJ1q4sIN4a0p7MrRcQo3e/pz9fsrHwqT+39BnH78mPl5ThnXOrsDObG7DOgXeEWKKxVL/JZlii7cHUlbkSbH0ukpsZ8OX2a0FXdmqV8ayZe8L1Kz+ZZrb/jmaYRsifJoQQ3Ocjcm4UM8qX6hKTb/9jrJ7XBO3v16KfRI+jJUpXZXydzwSY7a3ocmhfcSxL7elY7ffEVZ934kOr+xFoZELKbVnVbq55Cg7uu2Q0K1xIoV0rC8039+b/jTpVXGNrTL78LkI8d16e1ivBy46dPp1mpL/kdC6YRX60/NthM/LP6GmFw8LOZ/l0IaPNwnkOEnhQ+fR/fotaWzpveK990dQw9MGMfFaCD1a/pVwY9w1Nrv9aZow8BhrMbOo2DnkC1Zm70dCnR3fUpNm+4V6P71J+6sVE5cOqEvfRr7Kxo4+zvq1rcXeLR1IJ+4niU/qtKUWx5azKeaWdM5QXpwXdY2qzl0hOHLH0sMnj8k8dCf7atZ3YrMGn9C0UsXFrPcOs103vhTudPwDhS9pwl6PbsFOvFlb7L7+YzrRqauQNCqVjmw4yV5qcJndoj/Q/Z4b2dA+a4RyR/9C7w7pSpFDH1K5hX8Udx3qxNbeKyuuCN9ITdvdFj8ZsoN2XygmfF00mE1v9APLnK+jQb1/YM936Mle7HtA+H3FXGa+Uk54qWo0Ff06iT23egZbcD6WAg5VYw3vrxZO/RDMan5jEWfdPE358fdFm1iGziRvFc4Wv0Ovxh1hmfsyWIec12lOTDjVuWCjbc9tZ/ZjW0XnooVUKS2JmnV/SN/tni3uXWFmB42fC/czytGln2qySvNjyJoUKX63YSA72GSQ6PhjPHvO9ZA+XjSAxcz5UEi6WZW1NmQLQs8YapMXyRbdTKDIoO10+fmrbHftGXSm8/s0uNVd8dTh8Wxb4E/iwjqf0Y4bb5JtyH468mCK8Icph9jiyyUoqlc9GvXIJNQsb2TtBz8SHk7pSbs6rBZdJfrSphvZ4pE9X7J2pidi3aJ/ZiMGv84m9K6B6513xR+O29hfXoyhW7cr0ZcLTrN658/QFbZezO07hbU69KEw88oUWrqusfgldDrpwUWhevoXdPrMB+KC6w1p4YUq4gm4Fb/vd5gWTNjKjnYcKuZMPcf6fpVDb5w+RSvNdWmXI5Qy3ntLLPkJUZ/YLcy4Rc9iipWg3fPmsqDiTqHjsQ/Yt+8fovjxb9GDizrx7Y1j2KDqe8UP2txmJes/FDLDmrE5H+4QX3s8jmYM7iiMbHuG3d9+i2oc+5zlB1Sh+D+soJ6nhgvX9nVnzd9KZ67Y4nRhaBNW8+sqrM6xgazduldYwncrWY+J71F+vWBKnr6IHR+zTOg9hGh+3zfEHRN/ZmF/jmM/jztHb6S2Fw8EnmfDOu+gVza/wSaVv8wa5IsUebKdmLYnlmYFlmSbVx2lWqNG0JS7c+ngkyts8NFP2GzdY/HR8e70Zk2b8G7xs3RxdG3hpYlVWc/FjYQdM6uzNud60e+CH1BmnoF6P/6cDfv+iVjvTntqv3YsW2wbwkpc2i8Yd4UxatpK7Pi4NJX7+TV2KuswK7r2LbHhhM/pep15LPTBLBY7S8fShzN6MEhHLzZsQAE1b5OuTQdK6lWXst9eT1u7bme7l65irYPeo57PlaKOHYrQ6z2fY++JacKF0zo2oKYovFq/P5ux95aYOSuYfXZ3Gh0+OJ46NyojdhvWnvq0rczWFKvLijw=
*/