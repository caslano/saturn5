/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SAME_SIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SAME_SIZE_HPP_INCLUDED

#include <boost/numeric/odeint/util/is_resizeable.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_fused.hpp>
#include <boost/fusion/include/all.hpp>

#include <boost/range.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    
template< typename State1 , typename State2 , class Enabler = void >
struct same_size_impl_sfinae
{
    static bool same_size( const State1 &x1 , const State2 &x2 )
    {
        return ( boost::size( x1 ) == boost::size( x2 ) );
    }

};

// same_size function
// standard implementation relies on boost.range
template< class State1 , class State2 >
struct same_size_impl
{
    static bool same_size( const State1 &x1 , const State2 &x2 )
    {
        return same_size_impl_sfinae< State1 , State2 >::same_size( x1 , x2 );
    }
};


// do not overload or specialize this function, specialize resize_impl<> instead
template< class State1 , class State2 >
bool same_size( const State1 &x1 , const State2 &x2 )
{
    return same_size_impl< State1 , State2 >::same_size( x1 , x2 );
}

namespace detail {

struct same_size_fusion
{
    typedef bool result_type;

    template< class S1 , class S2 >
    bool operator()( const S1 &x1 , const S2 &x2 ) const
    {
        return same_size_op( x1 , x2 , typename is_resizeable< S1 >::type() );
    }

    template< class S1 , class S2 >
    bool same_size_op( const S1 &x1 , const S2 &x2 , boost::true_type ) const
    {
        return same_size( x1 , x2 );
    }

    template< class S1 , class S2 >
    bool same_size_op( const S1 &/*x1*/ , const S2 &/*x2*/ , boost::false_type ) const
    {
        return true;
    }
};

} // namespace detail



template< class FusionSeq >
struct same_size_impl_sfinae< FusionSeq , FusionSeq , typename boost::enable_if< typename boost::fusion::traits::is_sequence< FusionSeq >::type >::type >
{
    static bool same_size( const FusionSeq &x1 , const FusionSeq &x2 )
    {
        typedef boost::fusion::vector< const FusionSeq& , const FusionSeq& > Sequences;
        Sequences sequences( x1 , x2 );
        return boost::fusion::all( boost::fusion::zip_view< Sequences >( sequences ) ,
                                   boost::fusion::make_fused( detail::same_size_fusion() ) );
    }
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_SAME_SIZE_HPP_INCLUDED

/* same_size.hpp
foLXCvcX8H8V71yYZ+B9Ha/AexivHZ1gNf7rmA7MlgEDBlhtKfbUtHRHj569nAN6D5BPH5e77wn9aPL0/8qA7p4Tu3LMOKnrwCefknnqzv/2R59i0j/1JfvRQXCkYgX/jQnzUSrVP0hi8C8utVg6x6+BM71byifBS8FTkPTmXoCbCI2PnAeEJTA6JHhlyh1uc5J6jZPUrYpA4vebkxRU6xV+YFW6LPpfH58SHJXgcD5EB+6ngAoNiAF6iYBWKkB9TEAg4klViSMArF5p97Xwd9zoUUxf8w1W6mt220x9zcWzqaz5jGmJyponyTD7iSd+inlXu8NiZDK6lnUm3qiA491xR2FlxujFR6yvULrv64Thsr3ufZpCi4Cg4hZon8i4QdaAcQmzr9IqTkY60fm4Y2sq/06xi/+17VLofwad7KLEx79DXMi/0g599nc6oomXTN7kj+mGXEl7pV9qc5bZW2UxshdF9nziN8hCdK2HxblGFr5QO9QjViLufMTfpthgjzs66PgmHTvijr8nhGY4qkoVv2EWbD0Nf594bAqB5xxfa/3jD/u/WotJhMJ6LC9vS/Zn/TYm2PfTfmT8NMQvtJsAkvz1asFYXaVf6GxMwg/sMThdhr+msbN9bsweumawvbrFgpZKTH91Un4/pv2I/O3tJn+m/77u/C3J5RWd4EefkEOkt+w+9sYu4DfEwnMm4BzCf3SuU2T6E1kCcXoW5EAHaeeb3UvbykH2iEKBDk6Wk4IkF0jlndxQiYZ5BoUz8K64tlxKgw6tuZAnT28ZpI2OAbotAdATk2P6gMD7Kvx2RxREuFLtwljg3tZ44JAKrK01fSuLTC9NefmMGY6qvwFRGxuD4+GAeLgsrndnXXhME26dVk/8pvOm4iyb/HksXjTIpNnRV8LFg5uKZ8ut6i1TyG/k4AIueZ7mPTIjbyMJrcx094lRZZI2rfJjXGm/yooEG8w5YNuCjmi4zrw7YSBI2NA6anNrWVabW4yYoiT0it30tMFT5DEPxU7a/9YB+yN+5qndiP82nNSMhLu7pTSxNzLTDvqCmCZrxsNA4zmpZovvlJmaxm4930oSiY+Q9huQbgcktaHaNsWQBFyqGK0e7fpYvVJlZ8t8BtUY9B4z6HIzaDAW9CMGvYRZtpUxobuMhIbBKWH6va0ipun3BHnZvdT8HOwlHkYBwnLujNRlyXlUkmkKUe+QJquzGxYxFdAVQ+KciLyUrTILe8aYY/9Inddw/KrpuLhnza0cwIzvE23XyD7EHKzC1kl52akFa/v0WU11ThtqDw/6lxYr3AMs3HUIvfN/7jH0CTR2Wr+NBfH8ipgOdfTBrlGBuL5ypaU9eY425WuNOex51SgIkZieX3vG0Xmhe/tSm9QMoD1relA0aAhnHi754TqEYhccpD3niA9Tv8Jqci+T84VJvgxv3AtT9rGJZMX1zb9mNfXN7zYxtOT59QmJHFReq/Cu7vEhIhrf9MYrsxh7g+T0ir4hEyvSGo/IT/RJOeSLZKJeKLnwRs8T35SpejgNe8WSS1litQf+Y7rZbddxLu6t6mTwpSbK2P3eOt4eujo0cz6xyJnfNLHIQd1gkc0TzXne2FZuJCoZBgZ5dKZwvH/ILrdtclL/oL/h9/jk7tY/4tGlXNMT7WpNFyH0OC9rmKvhXNX9pPQG5SXw2rziGunqESMn2o5KyBGjEuFlHQnP6hWZBrx3Lzk6POaXkP7iTS5cIj5SCd/E/qRQwJFGl6KV9S0vFjlLAurudvl4/SyvT8pYcv/fGev/u9j/j/DfGvNvpn9Se1ZO0h1eUnV2cWgkwZc0kl6EoqglXeavClA/L//Vif7dzTePT1L9qYv4xOE=
*/