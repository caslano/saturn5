//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_INSERTER_HPP
#define BOOST_PTR_CONTAINER_PTR_INSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif

#include <boost/config.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <iterator>
#include <memory>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{
namespace ptr_container
{
    template< class PtrContainer >
    class ptr_back_insert_iterator;

    template< class PtrContainer >
    class ptr_front_insert_iterator;
    
    template< class PtrContainer >
    class ptr_insert_iterator;

    template< class PtrContainer >
    ptr_back_insert_iterator<PtrContainer> 
    ptr_back_inserter( PtrContainer& cont );

    template< class PtrContainer >
    ptr_front_insert_iterator<PtrContainer> 
    ptr_front_inserter( PtrContainer& cont );

    template< class PtrContainer >
    ptr_insert_iterator<PtrContainer> 
    ptr_inserter( PtrContainer& cont, typename PtrContainer::iterator before );

    //////////////////////////////////////////////////////////////////////////
    // Implementation
    ////////////////////////////////////////////////////////////////////////// 


    template< class PtrContainer >
    class ptr_back_insert_iterator
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef PtrContainer container_type;

    public:
        explicit ptr_back_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }

        ptr_back_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj 
                          = container->null_policy_allocate_clone(r);
            container->push_back( obj );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        ptr_back_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            container->push_back( r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        ptr_back_insert_iterator& 
        operator=( std::unique_ptr<T> r )
        {
            container->push_back( std::move( r ) );
            return *this;
        }
#endif

        ptr_back_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_back( container->null_policy_allocate_clone(&r) );
            return *this;
        }

        ptr_back_insert_iterator& operator*()
        { 
            return *this;
        }

        ptr_back_insert_iterator& operator++()
        { 
            return *this;
        }

        ptr_back_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer* container;
    };


    
    template< class PtrContainer >
    class ptr_front_insert_iterator
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef PtrContainer container_type;

    public:
        explicit ptr_front_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }

        ptr_front_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj 
                              = container->null_policy_allocate_clone(r);
            container->push_front( obj );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        ptr_front_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            container->push_front( r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        ptr_front_insert_iterator& 
        operator=( std::unique_ptr<T> r )
        {
            container->push_front( std::move( r ) );
            return *this;
        }
#endif
        
        ptr_front_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_front( container->null_policy_allocate_clone(&r) );
            return *this;
        }

        ptr_front_insert_iterator& operator*()
        { 
            return *this;
        }

        ptr_front_insert_iterator& operator++()
        { 
            return *this;
        }

        ptr_front_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer* container;
    };


    
    template< class PtrContainer >
    class ptr_insert_iterator
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef PtrContainer container_type;

    public:
        ptr_insert_iterator( PtrContainer& cont,
                               typename PtrContainer::iterator before )
        : container(&cont), iter(before)
        { }

        ptr_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 
                        container->null_policy_allocate_clone(r);

            iter = container->insert( iter, obj );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        ptr_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            iter = container->insert( iter, r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        ptr_insert_iterator& 
        operator=( std::unique_ptr<T> r )
        {
            iter = container->insert( iter, std::move( r ) );
            return *this;
        }
#endif
        
        ptr_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            iter = container->insert( iter, 
                              container->null_policy_allocate_clone(&r) );
            return *this;
        }

        ptr_insert_iterator& operator*()
        { 
            return *this;
        }

        ptr_insert_iterator& operator++()
        { 
            return *this;
        }

        ptr_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer*                    container;
        typename PtrContainer::iterator  iter;
    };

    template< class PtrContainer >
    inline ptr_back_insert_iterator<PtrContainer> 
    ptr_back_inserter( PtrContainer& cont )
    {
        return ptr_back_insert_iterator<PtrContainer>( cont );
    }

    template< class PtrContainer >
    inline ptr_front_insert_iterator<PtrContainer> 
    ptr_front_inserter( PtrContainer& cont )
    {
        return ptr_front_insert_iterator<PtrContainer>( cont );
    }

    template< class PtrContainer >
    inline ptr_insert_iterator<PtrContainer> 
    ptr_inserter( PtrContainer& cont, 
                    typename PtrContainer::iterator before )
    {
        return ptr_insert_iterator<PtrContainer>( cont, before );
    }
    
} // namespace 'ptr_container'
} // namespace 'boost'

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_inserter.hpp
8ekmoVoo/y0pWqWaeLpAsBnxBs0YpvbyQZxLJ0kSoxK4XqfEjrBeYg0V9aoMWEROeVcqg59Uc5u1jhtuPcwlAP6KoVwhWyeYfPdW1KshmZDXC+WQVs9XIz2dcXEtcfRiQc8ncb4RxEBOeXzjtG1xx7XNFY3o/5YeLnOeZM9CMXHHliwGwd4QPrqSHnlNcyLK2fmCraMAhSjqG2MC5VfU9YSqZBh/zujiWkjv7t3Fu8Wep3FTokOYZWAO2j4VtMy7tk5YuOKhK4lLyhdPfN0nq+OAHQPBCKuMi0k9Us2Lp5BqgrsFrU/0S0ci/xXk55kl819w0R/nLh0514bren+7/zTfrhIgUIBPiEyGyMS5EJcUjkuGuKQ4PP/7QGoSFmBu839D2lESgN8uUu9fCuFNpAF/ta2+uRCHKR8C+QLStPpaT7V+1doed4a7iOkhVTKkng1VfKFtXZlghXRrDCsZK6RdHTM/DSJueCg12XwG3kzwlmhfF+0/7W/nT6vIYXKcnMKqHuSCYUWLl9SZVEfKezJXjSzvSVmlZ/6z5fhX9aTO3Fb+ybjjIqDE3FZfohE3mfuDBzqJzQT9BuTilyY24Wjwezp7u3rZVPThhSKU+M0m3CMU9OKk7uAA+epxqnO5HvrBiE6sxD9DGkHvixIP0cRmd9A0hd5iS++wxTM7poJ8PLCjnQ+0fUwqRBMS8di3OFzpkdNG8oHvPnqKuDdH4vAw9XSWnnWBhCOkkWtlY6OYbNEDeQp9x0iDJxBFdM7OlCkm/otxni/0rtnpuvKUPgKV5fWiB+uSxOVZeJx2/41Q5XsS6tSL8P4OPtDPJYvFUA6fohLvD8NQT457X6SGTGsN1qhDUPLK68W7lXQTQ+nEL0uAtbSSJk9PlCvDhRCQLhkGwjAHH7hNx3+iZhuyxXI7oJq6P4vuBuDUbPKAQ8kf9Mu3YNk6hLxO33Wi52KohuaLtFIZ5ODRXCPdS+sgeZ3iTdCkeizjHXuoN6WoADPFtBxPs4v/tge1qHaDMNMAWIvn5xkNjTOT6M0jw+BD55qZCFEQpMEyZxr4n+hUgjpinQAoYsT0EEAoYkdgZbg4MgzrqccAGx+RJr5zHCCEGClCPJ3AB2erdXwnTPXdM42ZrJ5fZ1CxqdI83do4MqxSI6mZfW6fkTnozskWF/wnqqv4gMRpY/T1kj5ohtwFXMduqrIZJLtRrEHmfzcI0HypUVX2ZYjMumcZMyEpiQb6grY+Y1BxMJ0Y1Xrf3fxkFSbekI67eCoohLwn/hIvh4Am3i1xCfw9N3EMeW/vPSI6/qLlvo93qUehaUh0hGaSV+mIqphk9gZXV+fwQpnIWxOKlPkExGfsY5drFyx7hJoWfB44i0/nG/TZRZ9N9CnS5xH6fIc+8apv8ak/90niH8/3wfeWPnQcy6WJL50PTW0/X94vlR/YCzEqNpY49+D5O5g78XjWnXEqVfccYya3OF9cDUOt8K2k3042AWLZG6BP2VHQTZ+MI12e/ijPJ3qtsQb7CsT5w90zU8u4f8V012G6xGB3Qj9qdS4lVV13Zmo543wKUGVutp5iHD+Ht6oRgqsDQXe10+d+eFZu/Ss8HW2M41exKtUsc7ewww0BlhpMyGxaB4GuezszFq6B4VLHHCxP/5eJJr6Twc1Z5qDDkw2fJdGegK5QcG6CHFYPszEF8kipzrerk028C9EGuK2kGKZ4q6H4rKGYrKEYrkFMer0xeD9OHS+msPfxopa9gxcN7KSsLHYkddVzGKJ5F6Y3eA+G3nXeP4be1d4/wHsFfcf1tPc3oSiNl8TgBV03cTejOpd2MinrFQ4gLNZ+xvVEuET/Dgz0PgwhhPb94+5Y5uBh12xDi0wL3nsgSqjBlnmnKsX+aGCxolLsSFosxYE3hhYoDiqQlvK1AUuZx+aVX1rOzi6/9ASbVH5pDeM8aQi2B09yexsxmfUJbtQsJRCYhNxd3j2GIPwm787Qe4p3C7xXaTPu4MaWP6OeyiXx9Rolb3ko7wpIk2GmKW6XU+zGFFIZdI2cYj6mWMo45uDvY4zjbvx9knHcgb8c47gVf9cyjh/h70LGMRbvmK1BehhP+9blxBGWzeyryxZ1sFYEEaPKiXRXyE4gLhx3LkpvYulloFLtLLla9FuwF9VqkSkW4W1rB6NlUgksZZ7fR329LtTIvgWeR99L7AN4wtgEpJMqX3bNOF+JAtTVpTQ6kRBxy02me28+upyl4zwd3fU7f6cagPHnVZHRXGw4itBe5XskLupNxBX0v5zQhG0PU0InDiNHvw49QnFxLz70b5NNghMDCX02Ui6CAHmP4AVmeBH2BC1ehM2WpXkYB7YO4fdBJKGlDlERm87Uzu2VLaBczot91C8iDvFssW4qVaegvW8jZVvU1nxE1dzeSpqwkaZTq4IZZdi867G66BBNQ3YrydI5m9mpct30boN3VYILU7OJL6TVtQYimnInZJd73nszvL6YHWo1iIRfQf97R2JjAyuY52egnZljEu2+ZcwmLQ3/OfOrWupM4TF2PR/4JXsrH3iScX4JeOmm1ZfLqJCBN2CPP6H0DJTje5R3YqyO0B+yolfMipb9+/4URGS5hBTWWEycSFHFsCAyyK+CPowj791RIYzTojPl2mJxFqYBfg+OIcaBtxSSaFJM3GOMKD3bAOC1bdu2bdu2bRtnd8/atm3bts2ztvnuk3w/vh/XTNt0Om2adO5OMpN3iA2r55LOSJBqDV7gyv+E11GYaORBflwrwVc8IjYB4BC7qT4AS9376Hxt7oRwVQoE7bubl/omAnpM3abbbQiWD6rCsvfl/mY0X+NXHqnEcrv/5RRLiYFuVce3cB2VDD1yCXDdFFo5kg5g1K8ZM+/sDVpKzKNEOlFn+EeyCSsdisCFXDaI06mx2DIQnSyzKFEJmnOONJe69hXpjY47rDSgwiCCAj2VWnbxS01OW0PDD2D/kzP1KIkIuWwAsqrVYTDpO2RlOuEu5eJpjg49mQ5dh0P8w+5gWPXvYWof2Rz/qZBO6b5NYI14kEjQGVmlUBPxC/G7tgGOB6YWqmzepKVDTp+j3plP7snAG2Sqzk6I38aqx3A4cixKX9npc1GdJJNSB+9vELOTvXmxuE/gA6gm6OzNqPABNBVvuy+yGuzDadU9c6YHKjT1J/F7cR+NytiKOcAnoskZ64HgPq/JgVe+vSE3YUGgg+DJMTrLjydbSXcL1DMhniLYqWPyEWN6R8iiUV8jTjeOuuck1LSFXHeNMBGsfehFg+20GaUwGfLBF1ynBdoS1hmlLc7F0iw/DO4lF8hRNLHwOMWlRaAAJ2DOPJiLd9F9tssIIvZkG8uc2Z0wOsHAuo891Kn3UnBrFp0XnvVaMT3uWZuzWgfZH2CUkABnmfjeQRhHLthPwDsIo73W7k43NuY2qZYlt36z0DB8XJ/SCZ7o/EiTJxotq6Rqz20BKXqLBOk2OiLL4LmEh+KdngjklbSeq1TluV5EURpuDyr2Mi/CkrTP7KyI5XqTQJ8RBa2hdaKWi+ITYOWwU44OC632DD6yF1fl1fwT0CSJqt1fY+Zs5xalPF6xHhbcsFrPaV/aLSKnQ9jxoNpj3SdY7PNTLbTd2V3DgsK7UqXRk6GIBR7UmbYaaxJoP/Yj2J5IPjU44caLExjmVm6DLeOd79xWCky1+dutWPEyWqqwpi/j3wBB1R3486LrDUQ5mP5QlbyA0obsIBRk9n5lU7IL5p5DI/Efa+RQnFFp1Sh30jyXP6GNU2XC2PJRmY7Qhs47MyaLwr3SbJx7N8qvnU8v42TQn8n9u/6COhGOb04o9ND2p6kCbdctDmBmlZsbfdEoX/ohK+f2/ECFBZL3tIj8HboJUkpolhd3MGGrfz0Q2vTqEYMIZT7lWUb7L7j+rjdgI5FuuQZ6WSH50/uj/6GEqwDBuayzZAlQpK8JVuniBq1sk6iMG0Z9bCyTyO4tXg/WtkBE7MVGMZxKcU/O7dQKq6g00eAkyBoqjBO5h/Fp3LhsGaoVB6fT3vIo7R9SMyTxQ1tWFoy0V8rMpFV0AoK/g+HYM/qdWz0Dca1ImSrLd40OcLtq88Kp6eEgwZbovExw3QMW9m2bVhqZo5GJiMepHhAJ1u4y9FZM4Hs245Ib3q1pk+ezxuGwFL71x3IUpoQJ3scU0acwSbROS9/I9mklEFztVoCMlER9JOLqOUli5jM3kKKRTRVZtQxT04nHYatnsPVXdCpjnOElYZjtgRe+v75Pd5pFUZlHrwgMFK2aiiVOixlbp8KgvPYV4CsjHDcDhk9qFuIsbbG3PV2xCigN39Pjb3NmHMsfhop7wtoEl5R8TuwzcdI3lkwni86A9vSgRLpucsOzFKXXS7ZE6h1dxzEoiSwNWLI1G9nmGOB4YyTMz30vTtv2ZBlOd0Xoh20hR+xXiGkvjcWJk/RBRykfSGhEvgG72Y+biO98Ir3Uwbv0tim6x+kpN2/oWkRhtkLi+ZmnT3UFXQV1XmvtKR4ykzvAlEWWr1JAC5IAMkb2bjmGpQQMl6503uJykBU6TlJL60syiru20GXtaVDcU02UVLlvoiHDVsjr2I3l6XMg5aJ12YNd9GpUjH9xjOPanFmUMsQ2gw0betsbkVYliRX1YB2jKf2hbNWRO/vXu9xodgvXDY68m3QOoq6wpI5fiYcm8Y02SwnJ7uihKRMhbnq7lgQXYe6P728D+SLWzZmRPoYrukRGhc8ZtzTw6CFwYr4RQsms4oozOefNhMZubfDm3hQyipBYccsF+A+gE4R44hFJqeqNDNrYkgzfFBDjCL0N2siS9mfyiQgG2wRZwV2T0sS9kznGyJ7hIxfCGnHbpXBMvG0NktjKQIdstGuRwNdz8HBUEWZaXqkc42zVfvLYMpN42GFRATHD4GFWQ+tWF9lFQExeTQzaCJPyLcsgxurcBTw0ODGf2O4nowRo2VWrlq+AHP9g489vXxzZJEUmCKkUIajGpYuVWcIcPAdKKRwCtAj70uR/TcE0hbC5/ys8FOlHE1B7BrREukSvFi+nxOt43zGgPmNppX30HwRnoaatWWeM9C9WPPioUyDCXYlde8FuPtWPqGV/rZlF+8FV4w5dCQOkSzGgyAoM8Sa5NqoZYI5XLzr6p91GIpeae7M4aRcvVaQDQEYQPSWQsppMAAAs/9O94/UMzaLpRIssTJdi5vle41Kv8kO2B/GF6S7KoX5eipvBsXQ6WU3FtK9nuIwjPAI1ki/u+2DqcSYcrlepISxGV8nc+tZ00uI9SV9rZDxBbyzADMIy69LCOJPqGNWR7sg2eIOfuqM6usGMZ2w/7pHQzRhsTG5aZTpqTmMyuuWa0V3zeW9sY/R2TK5Z8sk0OpKirzcplqyvN0YbJiMZR4nIlE6QiMiESaBchzbGDfZAZriDmMYO+ABEAl3+Bd8tWRrRmTvFmEDWyIuoNlcXclJlpm3kCsWeTJK2rdaJWKuXbmZ7rDTuQzwuvRXrDY2ceQuVH0H7rdwGcJvbgpci3zQqXM54ctJ5fjYVa1VrbY8V+zbN/1lSH4gxNgUwDmmP3YpN1Bpt2pzGWObJKk2XOhjLNK/kw/Wy9yCA5ntdPCt+9gD4rgMh7yhHW+Wvy/3VRuhlwBnGsx34MdK4v3z+b2FolFtocSoWfa/nzqy34XP7CP4Gmx4Db4e9x/t913537Z3x0OPvgFaM7RpjaIsJt5BQrhVdvxOA9iDHNwNMbSuxnMxAZ04f2n0N7X3swk7zrTIo04NwU5LNu45g7vJt1VY9dA6cRsdaHkXc+KMqiwmdPLU6JPiKsWjm88BGHyt0a2E4I/hFuu+x7r0by19BjHCG4c66z9Ftxim+8H4QaXznVvGlacQsDBtbg6zTqsbPHMkGTxb5/tS2rASNVGRukJTL7tk5VEYJw1ZkrDC+OfJJWjXHwhTzc8fKy2g8BASVdSM13OYkVKs6gl0GP/bvCgNcKeC2gj9B+l5gpJqfATCaUoE1OM17IiKQ2vWBWygapaoHYYrtpMmO73H54ClMNfKO3OsRHqLx+P7jpM7Y+dUJStmQsONzP2Ajd2jTCNM2OuNlKj2xtNr1SDMUwoMceIEK0rBhjDN8smVffxuha697MvttD602dLVLldMo7uyKt5uSEx7UpDa047O6IWHsBlYO/b54tmpz2Rx6v2shNXB+Nyr80N0XXfh93jKwPd6xJHtm1D0LV+/A+SpYN9aQY5b2Rll4S9f2xWs444uKJcSP4SbPXvNk/EDD6fL6oMNMTvgCR98l6oLXtbf3z8B/vAUcRG8MQKy3a2T9B+xOaKnewkQjgHSdlHtWYVjyXJFHc58L73hdWvdEcDQvMNTlfcqKv3ExTr+Y8NwJ1F6TbX9ejmz9sVxBCkKq/zjWkutZ3pQ4eIfD29XSExfUt1/0VNb/DY6vQwQOqFIL8KHgW1rcoQnZbwEbzd0JNGFHhOqoO5O/xtvqLM5ThwfKHuD+OxCFFTVZVt/29/dkjWEey7hW7PLzSU0M10repuicLLCkMVd/yWsGYzRxVA3fXephvd9NlWFFM1E2UqBYeEQLf/xlXlhQT1GIBS1Rj62sEB2adUApU5/kC2Y2w8rgXBOU/iCZxokfnv7wb0ANh/3zOhTFWO7ogEAn6PNbI5tIZ0dGZ2xZl3XMp+J8GBsAW3XemTq787MfS4HT8YcUwg4/6bkWsOzbRwcClmHTiz8qMRzqnPpbgL0rd5nqPZJqiyEbc0m9COQJ1T5fr5xPtCwd7yBmZ7SpTfVPqJLp0KIhz4cfJiIeNhx5U+KgFFR6HQb5MgIsnswoTOT3fkPMOQ7OizJ+4/xf4HVgIFbIACb3WcAZ4VIOf2I6ZIzRScMEXMY8lRI0i5Y0BbBRcL8Rm64ecEslQ+nGJEAzzBHd1bKR6pWJqySoUHeT+03wYnQJ1rVnJNmYV4/Wy0EMhN0wjm9YNgUy+xI11CW/rv3STSeObZOocDsIK/4cJKu49De8Tq68FzGAdxUCoDlHQ4HC0M0uDxlBQOrdTpgXWCEBlYXzUKwqXTBRB7vBmgdR/9Gyb0WRYUD/NqMRRhquJZGChpX6NxJpc94pPooXNwnIYNU6/hIpjPywezM4JraKZhX1QMngNFWwZ+L5MQ+LiY9C4fd0WxRzbcfwYW5WrflZnYKjd0UFfmbC37QPwYX5UaNoWSGjMm40GOFOoCpQPgsX/t1k5lMM88XfCVQrJ5NM9cLhw1dhYtNhgSKfFdyIpJ0yBqWFYf3P0B23c49W7FYDSuj8Clyc6EircDr9x2g5EoCKDcoFaheahywZTLmlS48oVuDCpIhPw1AUNBEB05uYNNIAtjD2ClhDoucesCnBHCYUJLajP8voQiRTAnY33h7/HuGKkEUFm6ITZMh4aF30BGABvpVA52fbDY/B68pyneGhWTEuvceECh0XBnbdFduN86krYN2RMkjKCBvUnoBXoEHJ6bpNrhCqq8Coha/iuhCEs0MXyMelzDEE2JCDhqja7EZUEo/TkesYXrS3pnYPYrNsYJyoEPCPZQn70+XAQY6bkEwtpwQnpEmhiENMF0DSrPOMLGv944zKN2opUiwMg1GkmZxQhpUY+lEjSbncTIaRCghWrfOgcq1C1bCz2yJjxf7uSiRLf9CN
*/