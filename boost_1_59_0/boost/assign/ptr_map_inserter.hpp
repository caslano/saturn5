// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_PTR_CONTAINER_PTR_MAP_INSERTER_HPP
#define BOOST_ASSIGN_PTR_CONTAINER_PTR_MAP_INSERTER_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/move/utility.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

namespace boost
{

namespace assign
{
    template< class PtrMap, class Obj > 
    class ptr_map_inserter
    {
        typedef BOOST_DEDUCED_TYPENAME
                remove_pointer< BOOST_DEDUCED_TYPENAME 
                       remove_reference<Obj>::type >::type
           obj_type;
        typedef BOOST_DEDUCED_TYPENAME PtrMap::key_type
           key_type;
        
    public:
        
        ptr_map_inserter( PtrMap& m ) : m_( m )
        {}

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)       

        template< class Key >
        ptr_map_inserter& operator()( const Key& t )
        {
            key_type k(t);
            m_.insert( k, new obj_type );
            return *this;
        }

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 6        
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class T)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& t)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, t)
        
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    ptr_map_inserter& operator()( const T& t, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        key_type k(t); \
        m_.insert( k, new obj_type( BOOST_ASSIGN_PARAMS3(n) ) ); \
        return *this; \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#else
    template< class Key, class... Ts >
    ptr_map_inserter& operator()(Key&& k, Ts&&... ts)
    {
        key_type key(boost::forward<Key>(k));
        m_.insert(key, new obj_type(boost::forward<Ts>(ts)...));
        return *this;
    }

#endif
    private:

        ptr_map_inserter& operator=( const ptr_map_inserter& );
        PtrMap& m_;
    };
    
    template< class PtrMap >
    inline ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >( m );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class PtrMap >
    inline ptr_map_inserter< PtrMap, T >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, T >( m );
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

/* ptr_map_inserter.hpp
rCyTbcp4dSK9eovRNCoSPn0n2x/k70uDlgOsVIJQiuIMM3mv+/eWk+Lsl8VV0soLm32NWJdha8dbNIoswKcmGO+dbCf7hmHrzjabKYGn70C3AE36P9n7vZ+FncO+h776ryzjQMWwcrhr5JlcKfqn6wdbXTKNW8w8UHjivuB2NbD3r+snqWK7UWxacRERjVP74OCFDVRC8zloonCfGLejMx91kEL4I22jUt2gbVgGD/1bPcNz8GteEmeiAWjXsJXXmjIR4mRntLU0STDxoDxfWvhDjLY4X+hIKLlKB7AgsIh/R5jZDwDZAqjovck2Mf2VXOmYvAKVUSV+WKksouRqougvTeZbsqSi1ChaMIZWSW+tghP8pPW3gSzAuw2abEq0+N4rH2ZgUW+DhplWVGInFrXBTBaC+Ba/Jdr4MZkoebX5olOM22e+a/eteBmB/I5PSQL+VugA+DjOFpp3TcDtDUBXSh5FYwsiO6L2a+uQTphLl8lAnlV+QtoZLbnwyVgCrr0AlIOla7egANUdo94/FKIfVgEQ3jkA7oNeg5gHL4986J2IQhQejMBttnWXskSRD1k/wDX65YL7k7caZ2EuLZmsDfeYOP7V4GnmJNtF5KBxrOzRRQyiMUqWiIg6rDRi4sh4r7rbZqzYj9P5Gt8XwiyzwcSkwVNF/chEzGcu86hjj5WymAFw6jSGcYUeHKCsrpV+QjVj58mfLZdT10nfvZ+0ChthRDqlG2Vrkaetw5YPOAQbAfTOViCDTZ0CQUvQ59n+gY0QOyWXXpWyUjbjih2BzRGwgKLxNkaxZm1FBn8l1jpTB7NqvRLawOv8CqV8Hl3281glb+HYwhwSFuPH/lJKPIRbwkvxKD99SIn/MTpV1mJeLTw52dwgq/9WWlVrMTMKZH0yeuxtdjEa0I1Vufxjy8gA5osbCHbZaurDwj23RQ40TKbt2gr1TxjhNRCNerkG67Eo1WENF5gjWeeZevT9H7UzlWkB2LdQHcudP5WRowCQPHQk7HLVsZ0qiNQXnqKLBwf+Wpg0CWgYUUu5YdvzW4x8OT55MC0rYQ4G+CTz8x1M/2Po+X77d3haCTwCy6UMtBU3kc78h4Yi+PsV/WHKYue+xlAH+10QvdEFufoX9SF3opJH1JbLusoDajS9nFTKmPoxHd/Y/RS2ItH6lr1VjlYliCgJK+IkLUuOLdGnQ3DHSEL6zl857EeWuc6tsy/Xunn2Tz4IkRiv7LUyTPHDrzkP7YrKSPKAFj21niGhUwUDvOm7ZZadQsqMaGNrTe0kalf2J1e+7b3VYquaWlsgyMNJfDeY1uCdWfM4lge5p+6bP0C+Y42p5trA+nqVjhXwQV58ISrzhBSQszauLWdLJVzEkVycMUeGglgdMDHuDFSwpUeuDCtidmLhGLuVtLso1DcJ13eK3BOcS9KCRVS7mjBrNgS7oArwQcC4lZX0cvo6VhzlDQx9e7IhoA3EkSUqzofgEjWGOgr8xj24qyOzAj3tOhGzu7+nEaeEdGRqjZFDqA4hzNAUZq+l7HxC+7M6mDNrB2AWS4GJXgazr5HamiR13QjDhcecf83SgerA0uYHRbbgqZ8Oezw1J7BTPsaKKHaIOORnO7dLlF/tiDX2yP5LPm6ZHZI1KE8NT6zGTx7UnHxuNqny2Yo0tWbW7Ncp3WYwvWkIeht98xeVVs/zlNTNx4P+FmfVNgFA3WcwBHezqbIdbHYvaEYw/uXZsjXbQgQ/8DSw6BJaqILGLPCekmWrQE0qV4TB2yEav9Oszyxr2BnRLcBKVISD2aIkeu+zAxaD5MCdqhO4UBxNfOZlnceayDpwf7XoF7eel6N1qpHoUF4lR2unt7KsGYtr2c3S9cfyZamNgCG3rhF1M6Mk1lnRi7Nkfuwf828slpEHKLFj1lTWS8VUdb5khd64G1r4QQNGA2JP1wLGocyZf9oHhRwuF6eSGj7Bqx3nlqI9UUM2oE9ltd9SqnTbsuiwI6MVsywMUZOMAZBPCjz2Ru3WCYqDF/G0gJjwBMOCrKxQJ7JNtu+1NXl/WcGGY7dBomo/VBm+vxOe6uwVekcSPyAFex35qjY3hnojBB02rMAhO/nIeVmKfVmiKHPNHgM+rmCCm3R9CF00gtzGlXmNZi35sYp/U2Vm+NE84Ps2qr6MyHQXU9vPx+OiqbSO/6EgwOKzL2kq3hfPZH26cwfFvpDNIjTqDzoybcbczcPa4LP09cgN3EjYcN0QW8BNyVOwdtdhjx/L6v6Pccv7KTTDlhMIhZbDLZS5X4sQG/Z6WDfY1fABroLtBDM1APH36QkT+mDA5/eVm9lR2j1up1IsadNrbeu/sydvi2Us9ie6vxAxh96iDs5QxCm8iJqawe0Uy+BSmd0dwF9E0Ff3yF8tthdRyuwZvJkTISWkyQApyqwpvsnJy4ovNrJ3+VU2q73vYrBr1Xa9puciEgRRqRHKfEQ1M6ATBH/Wb8bWZxpZa/TwkVzkk3N4tfP8GaIQm+3aITuifHeNnmK8J3ZZkloFzdkXGeSwEHWMcrq94j+WNuWdJADnfF6L8xKOEwGzAKbOtaG7QPZbdHtI6OAjQPZ8f9cXuHhchMD4v+4CP+K/ssh19GVGBi/o5WiCFOx0c9Zd6whDCwuswxhsyVlAWmJxJ4FvigbdfVxnQHh35p579HAjawDi+3cSAUfhh915+QSsSc+4WbRr499ORK/vmwRkRQGMQ7UjI6gAx4O5111mAziDsoakfycXmez7IDwYB3zsR2RcPXk3GLlW6VGMTmneYXttyNlB7iUoPV+XWnh08zPdPCAnb9xykoDjtnI0sCbGaIccDFk9E4ITT3Z8cBjaPDAcMJNcqkoWpAyn2hx0qP4MTAwGxPFy74HMMxAkPDvs0Qa5Z50xfBd4R7nJP5he5a90zQhcFI6nPoGvwF9+b2TeXdqLXuy7fFuBOL2O73qo9rzIkAuR8rRiOQdIjPWiaVwfRVHn0uwio/PqlNlBjzahO1+quI8szUR0yJScsn7viDPwoyWu2M/EIgjRNYFMO+KvdWkhY+cIRs98HjAmXNN2n9UftMTe14Q6EFCDRCEDjmu5OPNsaYHmICvcrAmL38zlPGsCPyKBinM6x4hPP3IqPBmiQtZJpuAPvaM28uuvauf0r4YLPsNdgakOj5/slPM7efc78eUEcHsttwJQe387523NUA3/oQaio0PqVgCIKoF38rPQsPZ193N5DN6AFYbuhAhHF9ygzohFJvYufEDNUcYxrPFCgIthBSs304p1AegCqAOgBaa/naGi1v/T9gZ3QctC1fyIRrXxNP6et6tzsfZgxqfJiDKJaOhtYymdNcLmAmi9BoUPpAVSP7+DZHDlw4BDUcppAtWp6pw7FGh7pqjZjHnKlKlucLlKFKfH+SIdORuSEXvN+2dVFT4Et65oWVgdutWMPS1L33fGv2OqKbP3ytnqhsAkrmLb6liGzSKOpB+hXgqOZKk9r/E88uXUSHnobADlI9QRGusPYNqwDxXmYiv/D8S1bAU2vE3H1lqK6g6FlnqkDlsSg7Vs4iS2l/dtWsF9n7UfwCqpYhyTWCOXZyTLS4uGdGBcSJfFYiRt9CfphSNV0oJNvUF/Iw7d+K1Adr7iK/XRRiuZz4Dd6tPgMJ0iqBCiU9EyfMpUQ9hZWEfK0SujOi39gbLZDY1eYD94zSdqmN0RaqlEJQQFKDGZvBm1N/ak3wN/tUJ3Cu7rUJgHotdF+bCsNtjLU4n/8uHyPefFLfkDTCriyODZSf25OwvzuCECQT0eJFzrzl/jyxNlIyRz3S6dIVoRqX9EdGRvx2NT3Swwu3N9E+2X9bMVjpBEueh5LAq7l8FDUqCxevKqgSpWMPRLRl95oIIrWAvpUD31qBXgXESVErUixEr83m3FXWt023ipmxCbxRL5/+h64G2dYpHXQlj2RZBRc8v6s5fF4OnNm4vaYsi5FqVsC4CclHJg9oBjzZok9wDTgA4pYmWQb4+Wh81WejW72vTiWIvUtEJfF51FxsF45Yiukf2ur5Cqrqd3WV11uWWhKypEbUiX0ykaMdpA9JudS6URcieApdwUdKnJr626cff8mwAj9E5b/1jcvaUfPhERQD2qJFqFsnCxProOidC12P+IEHxStXK7114pSkJkrZLn4pLBENnzg5ZfczROEJeqdmQ5HF23DCHlmjBxmNXqueNBXsfEO30Hd1n6FhDS9d4FdHvTfjgKIFm6noN+A3HiUST77LhwrLNu16mu3Ug9M6K3yEBiIMhvQrhHa1qjLIDqMaMDHV64fExfowPdf/l/BJi0tzM65r/AaX7Jo/z7cph97tAJEGQHqm26biX9y32KTSPrlibHs/yM3LSzvpsIOKbgQ3J65wLWPUYfE0Jm+CHF4l/W9bhF7ikT2cRo58m5a5EQeRnWtB7NTMC4++QbgK2SdlqUx5zTsqzjK3zDuBlRoGDpz6871+1yZl1Qo/1wJejWl4PgV3qmHds+MpgxuLlUs52utAjkBOGpwiWMxro3jA6Q7n+SWbMs+RBF7awGYw4cc/Q5eDsBn0Arh571Fba+8eeiXrZRi7uJM7iMAx+O+W+IIQE+kXX2p7Ma75eARx50fHav/FjiwR9PvW1nv6erT0GOU/6sJs1lgEwZ0mEMb1xzNJVYrOxD4zvSimKLbqQ/ksj8Suy4l5DoS8XqzehrWPDrKbFkRpwcKcTGe8aQTmEzw1Yug0/Tl2W6LRTCVHL8X7NEW18V5Wb244x8WnzM9UTzsI0f6sajWcSh06ky01YD+3VYINybibtlVH42NR2sYh4g1B4LMfrRvT3KVt7cILsJTjXN5pfVH3a+mJTqLGnMLjhbiATnomPP0PSt/chnGAXuSmdYLYWQVOEhl7fxlmRZdrMXOpNKcfZAlS6ICvsM7ypO2rbPbvFTf6pog/+5+LVssPwdsdgGH8XjmAPjP2BHEcBqxkKeuCAjgdZW/fNWJp34SARJhzu0sfdUxVPI+QYr2I5g8HfGj+eCXRQLz3raJ0IBtr6qs93u51/atLS5+Kke0Eu/DMlSHA7M1Qc/GaP/3SQ7ZeRLQNixAsda8URzghJVP6tv9sVK9w7Je3QGXqS34h+6kVzUvZIWndHrbZjkbHMyWuy9JYYrG+9HKxze3oSXtOs37JCXNs+OmQvSE1jdf/gmtZkpB3SOe1yktcDT2R9aaaLjb4YXJjvGon9+Im96SyAnQZR39M3N+t+k7q4xZxOF+GcWsTrnsoo3CKkAzzbq7A/j5g1zXkyET5NCVRTylOyVxFvnFZc2Mj3uT55nd2PB/jVvkJT50M8VCi2vMr6zw79l5iAWMH1EZMVRBhcoGbOyl9AKTEJUfIdtYbK7HVjMznASrcvcnEeTd0yGmbyqZvOY9B9c0wVLxTJmZ8fhA5Z9EVB39PO+8t6BqufV8x2lJULgE/YWw+e5IK7LukC4O816Z5flAYCrkXvf1R5+up/aNe9m8cXT4wwofXHD5+TketPl0Q2eowWLEJnN5gx6k4N9ayNw+tp8BZsSf6jVifg7rjS7d2UrIEVlcr+a3GjAe+REueM748Z0J1uNrsS1E6gbx4BCRq3SCvY8Oj81QDMXzocOQiaP+qH5bQz4GPvTl5qbp5G06eFRFrlfMPDE2GxZCZaVWLyr3b4iSVjWROpur16YdIf4FbfTc8NnrPaQ2cLjYpjUBHWdnzt5sOiIas8uephMj1xN3MeWaFTmfjlX1c4QniAyTHF142Jc6qRXmC3MCIw9MZSLoWnXlZthl16QegzcLu72vQCBrTsbXxYF165fLTYcT0FJcvVcNWNBJj5Z1N4F0picV793V3msCE3sjIKyLqJ6D2rLWO2+RfpEkZFKf50b7e3MhYmmraYsp8n1QHcPvIB0nQZIypjqMrddOWjJTU9aN19U83/Jwv4gi2YQkFzDup6W2dmLfY0inWamKST1APfPyRwJHj61/RQxAqnQwm4OQXsXep8XZLwoYXlvEyy0PUdBRGONf2/cAYCCsi4Bq6MfPsUQeBOUb0ZzQ04377hsOL13Xs3apIXUaUGwy47QbaHxjfY25573c9Hghy5AarFz8Z2C3Gi+h0bAC33c6C1J2kZsZ+PeYCTqrk39LUEkt2D5HN3VC2swZmkPuoIo8YOjK49n45LNYEOLTXEnUGChV9JAnQKkyMgiR3mzDAvVOoRiMdWLZ+h1RGQZ9WJmcVltMO8Jqgus1/ADaFOq7qDl9v2csuFDAy4XoIXWSpvdP4EcNH01BO9AA/1jTWfjh8u+u7vvzgpDTXFiX7U/COaanXde9bC7lW6B3JQwamGsVy1IYxisEVtnWBdSMjvs/aJBey56+a+HkpAn59R2qnjQurmzfCMj88pg+O3V7q4Kq6FsKFgYI//Bj89mGX8ih4cu2x4Dzz+bDf3UnRPKcdngHO0oBIQJs8qV0G9Fn4iTKaXtWFJmVhuoemoGEh8Lm6Kgd5wzd9W4rVzylVu4y7H23Bk9mW8Jc2TZVvto3DSb54ZXUebt+I12dmdFmdCrbcI6/ZrHZzxuOwfe2QiPi5o9yjjKSavwVcX8nj0Xh1RrsppmI/xh4CtQS/u+kB+hhB4XaeNDlXkOrmzOrzkd7S8fHkr1bu1t5XIHhLR93Hem0wNNribNuVPDsQP/mX3lNqVcUzbIv7Yf9xHUZveKyaBnMT3d1jUE43huou2CuXp1uefMymzHswN/7hRy+jn14mv8CLxG/tVawKq66AGpPEh9QQ0tmnndmhIYNJY5Jwn2jatsxkp1Y0o5VdYm8LaWMvYRnJv6F81Q63DtAp9arR/tA2oZsE3QfSOnulpPZ4HuEzY3YO85e/mlTDWbhAise6sn4JjGBdF6a7oTPJfOC7Vz1Qr5ctHow/YL9lezzImL2/Pe7/MPPc85wWHs+bAjALVPzCzdj4Fx+q+hr9MY4w4TIFV8/HypDdFDTlDajst88dN7l0wGTsMK9JanhxIWNjz1VnC8jDjs8wv65J3qPxVcWwGUNZ2VzO7MaRG0oKUjZOBEsO7BjeTnyhAN+ucMKZxO3KcFTgnElC03kHMv6J2m53g9t2tZOl5zJcK8Lb142u1APtqBiJZQIebfEEpPvvFXeYcAlNsiYxCy728/6II4q/fcIsY7lixGWsutKpkXg4ddjYH8k5qSr0/O1g+b/be4+WfblfMfu3vIjbZBDP2NAHVCxNR5hjq1AJH9iKOE1dmeEaEs0opqfAmWUzjtAMzak0m1hHhJxSaWunVoTocLkeI30bKkkYRpnwXR8X8JxTbtlMs1/y3EnMX5smQfieT6JuZDTxIqYdWFtRKiFQc6J4czYJZpbZAXfGcYIUK0Xtc8txGqj/bTfya5HxDpVLSJxAfwNEM9uecnuU8gukH7JOu5Rd32LOqIUsei1bXBYeiIMzxzGp8Jb6asv0qcIfYxTBE1/bw2hSd1q17Pv3tVbTfr+Ts1QCRvsKoFdz0PMmg1mz3FWpT/xTUs6NFr/us1JOQ0NVZHXeFnVeBiP+FYvb8pWfMdOEWytFTMrHAyS+9V/w2yU8zMf3IQE2mxVWeaPmnwBCkZeP4G/GEaJdyOdaepnZgB7+N+oLwXyePbi8eu1yMao7NtCiJ614EtAimHJBtAXxj8jRjO
*/