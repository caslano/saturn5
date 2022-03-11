// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_PTR_LIST_OF_HPP
#define BOOST_ASSIGN_PTR_LIST_OF_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/move/utility.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

namespace boost
{

namespace assign_detail
{
    /////////////////////////////////////////////////////////////////////////
    // Part 1: flexible and efficient interface
    /////////////////////////////////////////////////////////////////////////

    template< class T >
    class generic_ptr_list :
        public converter< generic_ptr_list<T>,
                          BOOST_DEDUCED_TYPENAME boost::ptr_vector<T>::iterator >
    {
    protected:
        typedef boost::ptr_vector<T>       impl_type;
#if defined(BOOST_NO_AUTO_PTR)
        typedef std::unique_ptr<impl_type> release_type;
#else
        typedef std::auto_ptr<impl_type>   release_type;
#endif	
        mutable impl_type                  values_;

    public:
        typedef BOOST_DEDUCED_TYPENAME impl_type::iterator         iterator;
        typedef iterator                                           const_iterator;
        typedef BOOST_DEDUCED_TYPENAME impl_type::value_type       value_type;
        typedef BOOST_DEDUCED_TYPENAME impl_type::size_type        size_type;
        typedef BOOST_DEDUCED_TYPENAME impl_type::difference_type  difference_type;
    public:
        generic_ptr_list() : values_( 32u )
        { }

        generic_ptr_list( release_type r ) : values_(r)
        { }

        release_type release()
        {
            return values_.release();
        }

    public:
        iterator begin() const       { return values_.begin(); }
        iterator end() const         { return values_.end(); }
        bool empty() const           { return values_.empty(); }
        size_type size() const       { return values_.size(); }

    public:

        operator impl_type() const
        {
            return values_;
        }

        template< template<class,class,class> class Seq, class U,
                  class CA, class A >
        operator Seq<U,CA,A>() const
        {
            Seq<U,CA,A> result;
            result.transfer( result.end(), values_ );
            BOOST_ASSERT( empty() );
            return result;
        }

        template< class PtrContainer >
#if defined(BOOST_NO_AUTO_PTR)
        std::unique_ptr<PtrContainer>
#else
        std::auto_ptr<PtrContainer>
#endif	
		convert( const PtrContainer* c ) const
        {
#if defined(BOOST_NO_AUTO_PTR)
            std::unique_ptr<PtrContainer> res( new PtrContainer() );
#else
            std::auto_ptr<PtrContainer> res( new PtrContainer() );
#endif	
            while( !empty() )
                res->insert( res->end(),
                             values_.pop_back().release() );
            return res;
        }

        template< class PtrContainer >
#if defined(BOOST_NO_AUTO_PTR)
        std::unique_ptr<PtrContainer>
#else
        std::auto_ptr<PtrContainer>
#endif	
        to_container( const PtrContainer& c ) const
        {
            return convert( &c );
        }

    protected:
        void push_back( T* r ) { values_.push_back( r ); }

    public:
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        generic_ptr_list& operator()()
        {
            this->push_back( new T() );
            return *this;
        }

        template< class U >
        generic_ptr_list& operator()( const U& u )
        {
            this->push_back( new T(u) );
            return *this;
        }


#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 5
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class U)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, U, const& u)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, u)

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class U, BOOST_ASSIGN_PARAMS1(n) > \
    generic_ptr_list& operator()(U const& u, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        this->push_back( new T(u, BOOST_ASSIGN_PARAMS3(n))); \
        return *this; \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#else
        template< class... Us >
        generic_ptr_list& operator()(Us&&... us)
        {
            this->push_back(new T(boost::forward<Us>(us)...));
            return *this;
        }
#endif



    }; // class 'generic_ptr_list'

} // namespace 'assign_detail'

namespace assign
{
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class T >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of()
    {
        assign_detail::generic_ptr_list<T> gpl;
        gpl();
        return gpl;
    }

    template< class T, class U >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of( const U& t )
    {
        assign_detail::generic_ptr_list<T> gpl;
        gpl( t );
        return gpl;
    }


#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, class U, BOOST_ASSIGN_PARAMS1(n) > \
    inline assign_detail::generic_ptr_list<T> \
    ptr_list_of(U const& u, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        return assign_detail::generic_ptr_list<T>()(u, BOOST_ASSIGN_PARAMS3(n)); \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#else
    template< class T, class... Us >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of(Us&&... us)
    {
        assign_detail::generic_ptr_list<T> gpl;
        gpl(boost::forward<Us>(us)...);
        return gpl;
    }

#endif

} // namespace 'assign'
} // namespace 'boost'

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif

#endif

/* ptr_list_of.hpp
LDE75D40Yip4qBC+MOTxzykS5u99ym4LhMKQACw6xTFFBNkLX6EE2Ytc4cQ8yT80imWoZNKUaJxOzxewpb91GUYxBd3IHejYYvqufaZ+SFOI1Z9Ft2TT4jmBUaZlK5vqtQwIdiR82Dw9yU1FI5vV2Z1UDOqKk35s9lgjgOz2ydY7KAWGBqnJ/A3U/JThIWzGW4+QYD1GwEASuWgSi9IzgFz22IXOdCjAc3mpdliCn/Fn6Mmzo2CC2aqdJd32MGcGN7bLMRO9mNuLTq76tDQuBHIu4i9nvN7MWab5NdWgPZotTpt3eDaP2XDbtZ6hHfHN7tVw+DZG25e83VZr5lG03Ates17vWle+vGldciollkFnXAvY5fTFp3N9eeFB2LB811gbLeUKUoTyLwGYyq2obcIdRa1GrBXukDWCjcsVkQXGBUYF53mnee1Amn4do17/PE09Qz0hvEp5IXh+a2ieOP3CwgMxQxzr8ncHVFxWVKowpUGvS7PDJCh6kyqb2C4iCPp+WDppobSwj8mq9AJD4aP3ym7h+7D3Y3iD0wG6cP1D0S2YeIwkhucvFrlrKwUtgwh14wh1rUhNtUhNjcTq6n8sOgV4ZorVTeT8agpUZlSZTckUmoLYZcVR+BYoMfXR/5iWKGzVifStCpWEvv3B1IWPaU3zlQK1icxLS5Q+jZBL2vyV53WRW9o3X0v6SfWdiu5kQqRAEmBftA+CmF7XCxW+ghzrozBXwqHX1IkYTQyOw57UKbbQVauL1lmMo5k0/3VUS20rLXzHagC3VRR9xRkBTy5ADOsCd23xXbAuQTxuQoDVRYroVh+hWwBf1gUnIxsAf9aHN0/dL3VGP4fcYEGMp2yoT8jcXpiCRvXKTszYwgqtgqXndSBCPEIHY/sB9eT2IP47hR7G9nvvzm1BDF3d3aTS3uPHnSE1TrnzA5qhMN761sNYoTH2uiaM7gCvAXrTD7YAqem3ZN9pS1ZpeIUW79El2WlLUlE49wyugKfNessXGWAw9h9bcK93Pp19hzYPltRwXYtWjsJpcF0rnbFga7mdT8BLnujZJMhednwSLIYVWYbvyMjBsXT3cAZYKVEBax5hJjIkC/2zUCwDb6Ex2EzXVlsm+z5bLtthoZJLyfT9nX5SWhJdEljyWKLPetbpGh4fl4662yeIJ2ORcp4niBX5mGpJdtGoozHC4jIpK+eDkULvSVXVUDvPe3Y3j5x2/67NVcrEdxEtBUh1TdmOzYPE8+RBDF9VJu03/fdIQ8aZ3eDUtwoXfljmcLzOZNBYS1zd3gwPk+Zw/KW/3aryUMynAhNSAu6i6AIhi4cbXbUOmqqdg9JpoCgnisOLmqZ2CR8ywSl+4mEGKRntrgoEiaMH+pQYdW5MorBS1Am1tmPxwqYytHeCzBf0I8r5yqPjrL0NoQo4SKx8rw7lsanEXMsb9sIBnBjKrW02uzOTvvDqn+cqiK+jYkX3+hebsMrNbbN03XkOVJmfz+bXlYVSkKwflHLDIy6JxVY10L0/ujnfyzB4pSVpIQ6wALRaDKP3AJHVw2o0thZzV2cBcbuvRiekKXyl+ZC5EfnepcF4j1NeqYKmXExkf77IUVAPQ7iCTPM5J37iRnB1rhvHiAvlMYQy6B4heWw7PITtXbERG/hCK5yn7Q4/mzl4Xv1T+qfW9R/6oPInjI1cwJa7JV1D8C+YQ601CYWoM+Gt+EDOMNXYeWyyfH/RWVOeOz3/EY2H0WTUPfDgMi191sXyrgI8Ghf5p7DJlnMrYrnQRNs0PC3ac/jST+XpI06zSM2i/h0uLewLmpaKTokUaBpmeFEpLdgbe/Scg2U1SkcnnOjzELKy0UmFAcy76+aQkAPRSQ2iC8hrlBaJA48Uqmr96jmroU0F9OgYmpjpmGj9C3FsipQWbAmrV3QQmuOKNtI/c61wmi4nMFdeE7bim+sXnD27u1mRdtAF1LYLWZWsFpkhwwVOrfBatskWUJFMs8PEJdIGRubMWAcMDSymrWEblprhM7QqHDOcKrIqheenZE4NHKnaGjNtF7eirD4us93RmfhLZ1JvdD3PWQuc3Tj5lwU44jJFxQwKGWfj5VzBOiKuLM0uWz0HIirIPggeI5t2RHd/7JavYRoiMMPT9jLfsvExw4ZS9+4N7DS025qjdcdMetWI3MDarpE6Fu4FI6zFpGVannJ9TlMThPKJRamCmp8OoDPZRszdy08KImZwB7X4QlUOrTa1hVjjdAqZzqe8cMRGSoazJPc/j4UoDAucGtmYxItYryTdmnkzxWHXTndelWshNHTXKYjlGACV8x3yLIiVAEnNCvD6QzkhFfMT0krNUCrU0LzydNlHsjrLT18x2WjFlU/3P2Odtwnk5gGLXqEUa0el1mQz5gRmbev1SHTFPI7Ccyibw6Ex6eBRo/yxg0+8mbgSalAcdFRcR1fY8Wvcprm4qUEM0UsHADMUlFMZmJTllGG/Rpp/BubMzIzFMAKULCMsA3N+IOMTQMj4+g7WJWofNjh37jO+NXVRPBGrkWmgN8ldBXfLeh2mWUkMv/VaXTugeAhtOXaNd6+0ZHXw+Vp+epdBViemknZlcD+srPpCyqKqv66H+Thrhl6uiW07lmau4ZNUliJYKqoCch+ayeHxd+htTkXT+I6mpgFupG4mwedEGysiWJ7fi6qLWJw5O4rgNkeGk5gt3qM2uiv5ZqanNvyo2sL3Q56NG1Yq90XxWt1MZyaiOPDbMiq1t3G3J8FLntiB21bIObsv3H7ywLWH6wPs67fYg22cIZ3FnO2c57SGXOQeFF7sTBo91O1WyiKsgwzpPF55QZBBYBC/oCqwxyp8rPxQ+oGc2IsaE7wXZ/YRR+lJydOFmoYJFEHIkuqgAoc/eE54V2Y+FwHL8aItLq41jzSb3jw5aIUY8Q0cjT2r35lkTP/G3aY+KZ02RshQemqyuVcAELpIhWL8ecqfB3DopNpMcdy1HDtE7AGhuQBBfOaz9GPcmsIT2UKvmpL9zILCb+nNfSQ/FVxG3WGhGsxdIYkWHeaiuuoVF1NHnQHhs4fnISsL18Dq2y4xDjdFXyM2wyZlMfZ4XkFbh/H2HjGCukPyj8DHXlZO5I70oIGQhQNIQeePAN8QyYo5kk8UiMBebbEnOIjM/cMkYYuzt9niQnAy+T0eeJAXktGMfgk1EV2AhGrYV7of9kLO0c9SdGWfsR/1zB7//a+A8Ih1qjJL1d33AkILVZb6My7oie/m38ifi/QHruvWg4fdl+cDZJ10p24iT71buHKqbhegLQSTmAP8ZivY2SSjHGRO+vYGG1hrZjJrqfqpFt0xQ8p4TDAwvvV/xTOx+GSLDusQpVNo+DPsdjYQhifSU6QNIMkJOysF66OGJzJTdUsL66FVU3n4opcTgLM5yF1CaRLzWva2MoXXktq5nQkcwk/hV8WMaoSa98qqAhwkmibfakHOwoke0dXZ7/s1hH0L2A2yZHBoQdJ90kHSYtKw0nLSqNJp0rjSfk/xVVBVSCfE2EzY/imQPkl3DVJySfaoLe8zRp/+Gu5u0r4yIFQU50bcg9yL3IHMZ+iFtdD5xmNU54eQIwq38bdIt/JYQ01QVsZxJsjGScYnxlpUAteEN+M3DNfrN0DX99f7N+Y3/TfiN/PX6jfeS5Ruf6vi93NFBOFAf9DQi/XDIyByIWJKQiF+kLOfRcel+6XPxTurbut26xC6Abrpin1dlF8GRwk7tGMiejNGM8YzJjOmM2Yz5jMWsZdPtS6IT2geqg/gFjmLFaJ5wX1YjjFqiKgCornZvVSPexf76khctewYlC0GjXvm/DqKiALqrwCm+SsLDi+kB/aiPjo/vAK9Ej0LvRs9QXxQvIm9mDYLN2h5rbieuKe4o+ww9mtFDOCEv6JNv5Hp8+9QOdQT7DYNOD6S4C4zzQ8i1EcawYMA6Pjo+EDoAAhAUYBSNzU65TdAOZucyJ8gnv4+/XsyfQp9Kn0afTpt8bZE6sErvQzgieBJ4M5QvmABzW3+0lKtobimuKP4pngLR+DlMcaoYSnWiqZ9ozij2KMA5UXjtTN7vMR5Ub7UPEFFIzjPnq3eK+BirnKSt5s5zluKayvjZO7ZA9yOy1E65dBwiVmQa2HvJYkNATISIScklyxLZ4VKrAh/Axe542yS1b/+GyDGmEBgLFaY/7dJTn/qb4hYhyBlAt85vtmQmBuDedFgvBxawnKOXwaFirBoCfaLK549LrnakM/SR1/OTfqF+r4V9Z1kvnShNIUElUS9eKM4hwSXRL+0ImYUVhJmFkYRbhVGE+ZQUYfQPGl9bEBOH2+cQ76PzBfCIzXMm4rbwYDaPieU9lxq24QVtdBcdiq3mVd+4M6BjxKb9+xJ/twSjWgiAwe5SeO5VAVzFVlL+mLmslGYGd0wlWhTumqVNdVIU7r+OeKC/ycCKucUCfbEghYMY9mAmqQTy+ycrgyNR9fDezhYk8yTDOC3/wxvDujVV5WT69GhCbDvzp+yAwNtprUZLN5N5s0ARnBSqZhyXJXNmS4sZKf2H7VI18ZLzTq5da1hrREt06LCrkNNOwU7BScFPYWhoPfw+3CsHKAcqJx5xjoDR9PEmcKJvZGG24b7hseG54bdhv2Gw4bjBooT/Br9mvIWHBxhfCN8YXwlfFB8VHwStnMacx0oHYqd9AAHUhHcC3ucoFPbtO98ueGAYyMzi3YREGqK4ULecdLgnmQSeHGHfgloEYkHcYkIaQlI7LllASswTRhuzKRMifxjNVWnTELbjwLYBJUlq/tVxXkJUrRZqiLVIEsobKWV71WqVlX3egr2lL1pUQ1SCfJl6l2mxapwzcT2v+w0mljxjOZahzx/PZJbU8LryhWzKLbKHfXGwNXDdWbxgo1pbtXOtxqYDGvO58Zf1I7N0UKnseuTvZN9jvvGAlq+RUFTfyzWOvLq9xkMrTiY9ZuYzLMmeevDFe4PjcQfSEqopqvS3XxQuykbJY/ixytTFTE6VjRM2Y/MECYr5amV2EHtppcqVT8XdNPWsMoXFMwqlRWa+92rz+LX6FhL3eeVAroIHazPgbaSG+lNLZSb/T3MX7W/5p4R7/m/KTZIVoqWi04+BlS+awRUX//h0rqf7NLkuW89dpCvkNpInhNyACs5VQ80/6ncwj3EDszu0+Lm4QKjP1nF7/z86g7+ZF6jfDwxh1/dPOAx7s4DiiSGj3iNeGWUMNF3eaONvJlynUSogbwBnlt6O8HYTAjG5BWlj2l8ark0YZGaDsWX1Rnorc6y5zxeLYcNL5hU5rY6f9eAgV4yO3NmBD/nsUzPjw6fznBN0GgB4xasEagJ1lzJGNomdvt7G+uJ6MWr01D7Ro61r8LYlZwfXRj+jAxUDirTx+plL+fcn2Qm9J3jpPsCdfJdDmzh1zhN3phkQMaOo1/kRVw+9eJbotFPKNIUSNswb2B0QuzV5uU7Jmrp3USNdMbLFnVp7xW6hwF6lCW11YJwTfTF9uAN/oh3qMAxGl+CYJQXNZkf25ufN5jPMJI/MBlf/5eGmXWDrjRMU64e44xoPAYOfAv0CnoP+gia3DnlLf5b4EX6w/oh+qP6YOsx7mnube+H/zWGcG335XRgx+KAQt/J4RUA5TqOS18L5Gyg2PcZPj9ZFS/vMCPrXAJHtYIXykUWLwj/36ugYIvDzM6r9xCVkAa98bA1boUdtW4/nkUB7cDVLQDU7jHF6bQ0V2RkuE24+fAmoSOFV5DVWDPSpAjHM7NKQ5PweyYCp/eZuNKRaGSum5CKOMtf4+Wf61eDlllHQhcqFwoXQpdm55iPfk/p995DzE36cgtFpZFuqg++ZpZaM1OVk/bJldSoihwt6hZ95+tXgGesG9jm82ij7hA9nWlEq+Ne76UpXALOMELmXibukFZK6xh97379nXK4+GHqSEFQ8PKDsguS3SBXlz1PYAsZb0vsIumu05hiNLAt/M1pz6UNsNqptP+eKbmhCBY+vufhHF4u6bycLqRdQEvOYD2WDiBnj8LuLPHOVMFXPMk9xF0GdN12u+86AXOyHdKzyQQTMrI9UpeytW1VQA7wr4E8/DsM/MUWXpOPHw6kXmGLusPeX0vWHqNZiJb8QLYfw54eEbWnfV34TyqD8tRhnxbjZsAfT4BWZMa0BGoZ3WwLvHkWG1hln9GAxta5JpZxJwYPp4zD2Bcgq97tHoKU05hToI9hNWkUTubGEp4EKoqfJLRjQuY2dtrdsz4h6F5SHGKeeG5mu/oI7TpGvL/9dvbo2ypzBA7uhQ3o2qx2pGPHDNsiAcJIHITJ61In5Q2KkdXEPavbgW0KinRnjZSTTUwbPaOJsIzXolOuRR9xN7oQHbM+GkgNHtWfZwoWk65KSpSTcFNoV8uxrR2Qpeosmt23Bc02Vapq1LJVrHK+dyWSPG47bQZoaWtXL1l4XJgFpZax4b8g7TtxtwUnP6hF3a1Zg8jdr19gJTQmZkIcfYeaKp6bV6JH4hA+I5JWMqZf9AXDf2Tux94iRpNbgf4x7tPzKyFYB/oeAjZ5QEbJoN84NS1N7/otW6lAA/ZvxYi6V5a4KrBUxOKbTbrghl+kjwn4m+ZcceSGe1Ippkrqzg+mHsEm3S4YJJXTP8EdPrCactaG4bD1cDYHATTsJe8kohfSuipbyDa0YiBh2s1omgBoLgpshtqtyAiNrm5a6bzjkBMZCjb1jZfCyk6lF9LgWMuVqFFlryx+lRq9at2mRwPZ4nnIPojhx4SjQ4kTcJRtfkVctVdt60OgsVyDP77jyLZIcIL4YOh3mGliOUq463dhYsCzvQNMTZwG5VUiCGcgojjdOiHwYPNsWlfPghTwCHaoNl53p4RILKgLzVkT+Qfu69W5geyMwh6utLrnRyECtVxCGtxHZWN8Nlux7qzuIISXxPvzRgy46c7oOza3vX2IBwWpup/Wy3IrqIbepe4ycb+5ZYvt2Enhesdwi0LUl4YbvFmoLKOMngKdOdXz5CHgd2gVJNJonI/nWuJ/uKAqUzYLVftYtAJVceh2ou1sugTxQBMqW24As0aOIzpgVJc6371WQ/m1cTcwwW4VPOKFqRv0zR4xqwdFh9SnUTl5W7ha9G4AlITTGuBhZ5mwTLmFLEARtTPXfbkmlaiM+HI7rxJN4Qj00IJjel5hkctUfsFOlBxdf4PZ/834Mbgznhh91IyDPLcGH/zEbU43hx0G5ntGicH/6a4RWppQinxdrg1tdum0/xpViDprF8hin7Py/84+BX6vs3RBP58EelLuS+Z6mmqRzlKCHrbbCc6rJ7zGfWHOM8Nf4XvfbV6IKKXgS3KWqbKRuEzTnDUXPcYieFgkXYNzxzjr1GjBRpYpfQHf2+XZQf2ZHHKf2O67eBMxCsW1gT5hDiUJnMFStksd5HzJflxPur6OM29/88ZX4V46BO9U+P6o87xkg1aB0vJTA4D8ok2Kgkth9vQ5Eb40R4i2YaH5FjSGpT6USe5b3tlmEBVNAfXBV0orrHHNXlh4MhqEK95Zdwc0eolumzt/Kt9y9bSNgjcEft/+u51PsKBPniWL498I+4lh+E1QIXDBfx5E8tjpiqg+6Z71t9ynO64T7xVgcAvZrdd1O/hZK0E6PqDHoYeXH2rS1/qgYDM8ijhKYSWgkplop81ADu9RL1XB7X0uDXdKOpGsFXUqZPPkOWoQoh+2J7TVtwPQg5feFlQYmaPYH3tPEoT5tYtPakgLNOHGshVCOlXM+ySqL+q3/hUUAB7L7zn+I3mGdLThRZ2nluLq20txcsbg0Rk1AZgQ4HkTQgVwFb5/JpzjhDNG+xNli6ge4XgynAd8pc834O4/QzTuB1sSVp+1tXAe8QLliMGgO7mGlAKjxBq/SMt85PNzPMW3hJVdCJ/JU1K8LY/bq54KFxaJvgiyhZyNQk/PtQuyRNK/NIN++JmMR/BuixzvYKNC+TxYS2Q8Ew/5W2Zc8ZX5zR2LBvyD02Nt6ddFFuyeh9a08nhUOMM4HatIp8grCX3x6CZ7rucF/naRnsSR/gP4zv+za1wbI7V3T20MZyjHaBxZRWxwj5r+F7lK7wJLqJYhb/ZiKQPTYMiBB1zUojn+Hy45PK+2E5O1rQQtL62fOOGrWdmpJWbjKjhYSEia5sAgnLgc0bZRKbjAJc/S5BGNP7TFE7uOqY6nj9439qg6f8vlv34XIvMCFr9mlp7d6EU7f74A3e5LVoLMG4BNbxnaaOZACIBVp5OL0ZyjF6yzebZprL/FAHhhE8SIwvlE/J9FbcW4N+QMyBYl94comu620lZ0wlAEEaA/L8n3OA9PR783W56hF3SHzb90HzVXwodK5gqu2NFW0+gNmYdW4uWCtikH8OgVUWjYim+kiCHIZpZomGoRA6QjZkUDdyi8wiR4LhMxWZpdZDdcEGNVzR13im3j3fRi+7rTWVaD+ffL/1xcm88jPbCjfWVt5dGxoBuxoRfjR1t54t09ONryM5oyrYKwWpikJA4TAN0iYlWPmrxciw/SpsuqlgTxB/asgTvW4Y0Dm43G2vNpw/JkTP/e3vpTrUqyHiad0CuFti1DTb7NfKSsF7GcBqxXDlZ6N8yrvoCQwIUMy6/t5ysvbufns1iOjjEIyohpRvbpTR2lUiNBQR5YaaVPSCzp8iTJMt8uVy5CCqjV8VBPPqjSbxVYrH8WebWxX3GjZBcycyK5zROa55nT18O77VhnssbayLjgMu8MOjhjv0UIuTX0dqacmQZMSQxqNxpJ1ct3GWuWTDh+b8yBbeY/VN/iz1IlJKUhn3daw8tDfOjBPOeIkM9j3ts/9o41mzAcSe1puWOVM4tNbidZtSMrHpg5BadIj5hFLJYQjRS2WkY1cyxV0ng/OdIoYWwGGgls51hijcoLsVxSDS7mP1I+FG1hl3xtdlY57zuznZ70CFEP0p+OosZvTCVqXhLVprb+ZabC/luJ8DeQkyuiljkNIo+VfMpJBDgSfBhSFugtjtxN8THXFdWpYtbwcZ9lRSSjvnz24vh8ucwr1MGXudlTC9boD/yQinQ7AtH5zT9xKp97aCpcXJr27LTkQHOfh+B6dlbK7ifH+Qp4Fvo8VBdQ0LawCCLVCPiL20effefyY3egWX9MHzJ2qTBpwVgL7DDDgWSEUnX4jhZrJxbkjaSuJp1JKpgDPEwKlgeyBgvHLBmN/GOcuya2PCnBDI4=
*/