//  Boost string_algo library classification.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
// 
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CLASSIFICATION_DETAIL_HPP
#define BOOST_STRING_CLASSIFICATION_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <algorithm>
#include <functional>
#include <locale>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/algorithm/string/predicate_facade.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  classification functors -----------------------------------------------//

   // is_classified functor
            struct is_classifiedF :
                public predicate_facade<is_classifiedF>
            {
                // Boost.ResultOf support
                typedef bool result_type;

                // Constructor from a locale
                is_classifiedF(std::ctype_base::mask Type, std::locale const & Loc = std::locale()) :
                    m_Type(Type), m_Locale(Loc) {}
                // Operation
                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return std::use_facet< std::ctype<CharT> >(m_Locale).is( m_Type, Ch );
                }

                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x582) && !defined(_USE_OLD_RW_STL)
                    template<>
                    bool operator()( char const Ch ) const
                    {
                        return std::use_facet< std::ctype<char> >(m_Locale).is( m_Type, Ch );
                    }
                #endif

            private:
                std::ctype_base::mask m_Type;
                std::locale m_Locale;
            };


            // is_any_of functor
            /*
                returns true if the value is from the specified set
            */
            template<typename CharT>
            struct is_any_ofF :
                public predicate_facade<is_any_ofF<CharT> >
            {
            private:
                // set cannot operate on const value-type
                typedef typename ::boost::remove_const<CharT>::type set_value_type;

            public:     
                // Boost.ResultOf support
                typedef bool result_type;

                // Constructor
                template<typename RangeT>
                is_any_ofF( const RangeT& Range ) : m_Size(0)
                {
                    // Prepare storage
                    m_Storage.m_dynSet=0;

                    std::size_t Size=::boost::distance(Range);
                    m_Size=Size;
                    set_value_type* Storage=0;

                    if(use_fixed_storage(m_Size))
                    {
                        // Use fixed storage
                        Storage=&m_Storage.m_fixSet[0];
                    }
                    else
                    {
                        // Use dynamic storage
                        m_Storage.m_dynSet=new set_value_type[m_Size];
                        Storage=m_Storage.m_dynSet;
                    }

                    // Use fixed storage
                    ::std::copy(::boost::begin(Range), ::boost::end(Range), Storage);
                    ::std::sort(Storage, Storage+m_Size);
                }

                // Copy constructor
                is_any_ofF(const is_any_ofF& Other) : m_Size(Other.m_Size)
                {
                    // Prepare storage
                    m_Storage.m_dynSet=0;               
                    const set_value_type* SrcStorage=0;
                    set_value_type* DestStorage=0;

                    if(use_fixed_storage(m_Size))
                    {
                        // Use fixed storage
                        DestStorage=&m_Storage.m_fixSet[0];
                        SrcStorage=&Other.m_Storage.m_fixSet[0];
                    }
                    else
                    {
                        // Use dynamic storage
                        m_Storage.m_dynSet=new set_value_type[m_Size];
                        DestStorage=m_Storage.m_dynSet;
                        SrcStorage=Other.m_Storage.m_dynSet;
                    }

                    // Use fixed storage
                    ::std::memcpy(DestStorage, SrcStorage, sizeof(set_value_type)*m_Size);
                }

                // Destructor
                ~is_any_ofF()
                {
                    if(!use_fixed_storage(m_Size) && m_Storage.m_dynSet!=0)
                    {
                        delete [] m_Storage.m_dynSet;
                    }
                }

                // Assignment
                is_any_ofF& operator=(const is_any_ofF& Other)
                {
                    // Handle self assignment
                    if(this==&Other) return *this;

                    // Prepare storage             
                    const set_value_type* SrcStorage;
                    set_value_type* DestStorage;

                    if(use_fixed_storage(Other.m_Size))
                    {
                        // Use fixed storage
                        DestStorage=&m_Storage.m_fixSet[0];
                        SrcStorage=&Other.m_Storage.m_fixSet[0];

                        // Delete old storage if was present
                        if(!use_fixed_storage(m_Size) && m_Storage.m_dynSet!=0)
                        {
                            delete [] m_Storage.m_dynSet;
                        }

                        // Set new size
                        m_Size=Other.m_Size;
                    }
                    else
                    {
                        // Other uses dynamic storage
                        SrcStorage=Other.m_Storage.m_dynSet;

                        // Check what kind of storage are we using right now
                        if(use_fixed_storage(m_Size))
                        {
                            // Using fixed storage, allocate new
                            set_value_type* pTemp=new set_value_type[Other.m_Size];
                            DestStorage=pTemp;
                            m_Storage.m_dynSet=pTemp;
                            m_Size=Other.m_Size;
                        }
                        else
                        {
                            // Using dynamic storage, check if can reuse
                            if(m_Storage.m_dynSet!=0 && m_Size>=Other.m_Size && m_Size<Other.m_Size*2)
                            {
                                // Reuse the current storage
                                DestStorage=m_Storage.m_dynSet;
                                m_Size=Other.m_Size;
                            }
                            else
                            {
                                // Allocate the new one
                                set_value_type* pTemp=new set_value_type[Other.m_Size];
                                DestStorage=pTemp;
                        
                                // Delete old storage if necessary
                                if(m_Storage.m_dynSet!=0)
                                {
                                    delete [] m_Storage.m_dynSet;
                                }
                                // Store the new storage
                                m_Storage.m_dynSet=pTemp;
                                // Set new size
                                m_Size=Other.m_Size;
                            }
                        }
                    }

                    // Copy the data
                    ::std::memcpy(DestStorage, SrcStorage, sizeof(set_value_type)*m_Size);

                    return *this;
                }

                // Operation
                template<typename Char2T>
                bool operator()( Char2T Ch ) const
                {
                    const set_value_type* Storage=
                        (use_fixed_storage(m_Size))
                        ? &m_Storage.m_fixSet[0]
                        : m_Storage.m_dynSet;

                    return ::std::binary_search(Storage, Storage+m_Size, Ch);
                }
            private:
                // check if the size is eligible for fixed storage
                static bool use_fixed_storage(std::size_t size)
                {
                    return size<=sizeof(set_value_type*)*2;
                }


            private:
                // storage
                // The actual used storage is selected on the type
                union
                {
                    set_value_type* m_dynSet;
                    set_value_type m_fixSet[sizeof(set_value_type*)*2];
                } 
                m_Storage;
        
                // storage size
                ::std::size_t m_Size;
            };

            // is_from_range functor
            /*
                returns true if the value is from the specified range.
                (i.e. x>=From && x>=To)
            */
            template<typename CharT>
            struct is_from_rangeF :
                public predicate_facade< is_from_rangeF<CharT> >
            {
                // Boost.ResultOf support
                typedef bool result_type;

                // Constructor
                is_from_rangeF( CharT From, CharT To ) : m_From(From), m_To(To) {}

                // Operation
                template<typename Char2T>
                bool operator()( Char2T Ch ) const
                {
                    return ( m_From <= Ch ) && ( Ch <= m_To );
                }

            private:
                CharT m_From;
                CharT m_To;
            };

            // class_and composition predicate
            template<typename Pred1T, typename Pred2T>
            struct pred_andF :
                public predicate_facade< pred_andF<Pred1T,Pred2T> >
            {
            public:

                // Boost.ResultOf support
                typedef bool result_type;

                // Constructor
                pred_andF( Pred1T Pred1, Pred2T Pred2 ) :
                    m_Pred1(Pred1), m_Pred2(Pred2) {}

                // Operation
                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return m_Pred1(Ch) && m_Pred2(Ch);
                }

            private:
                Pred1T m_Pred1;
                Pred2T m_Pred2;
            };

            // class_or composition predicate
            template<typename Pred1T, typename Pred2T>
            struct pred_orF :
                public predicate_facade< pred_orF<Pred1T,Pred2T> >
            {
            public:
                // Boost.ResultOf support
                typedef bool result_type;

                // Constructor
                pred_orF( Pred1T Pred1, Pred2T Pred2 ) :
                    m_Pred1(Pred1), m_Pred2(Pred2) {}

                // Operation
                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return m_Pred1(Ch) || m_Pred2(Ch);
                }

            private:
                Pred1T m_Pred1;
                Pred2T m_Pred2;
            };

            // class_not composition predicate
            template< typename PredT >
            struct pred_notF :
                public predicate_facade< pred_notF<PredT> >
            {
            public:
                // Boost.ResultOf support
                typedef bool result_type;

                // Constructor
                pred_notF( PredT Pred ) : m_Pred(Pred) {}

                // Operation
                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return !m_Pred(Ch);
                }

            private:
                PredT m_Pred;
            };

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_CLASSIFICATION_DETAIL_HPP

/* classification.hpp
cEU1c/1BHkzeD70XGV3oXXx5Z/azrtsPvYOS6D09id5R13259HZ7H/6DtyhtWjdaKtgyw+y6rKo3rAfXvZqDNdhHSLCWux+sb9kkJpTSuzLTzM0Py/iwBGHKerOCOllPmFtYVRTcsUiCgl9S6A+yatAbQcikEhphL/PcO6ER5gLXR9ndoRCnSfy5d2Zy/OtU8GX7ZPfINMluhKAfprILKfSBnN0Yl8rvHMpv7R0CK5Aou16RKIepKJ/K0k0FZr2w1B9q/hHorYVAfAuIrVl4eRcv5uaHVPnFX7VH0bkcwcn0pSv6nhC0hSqzp1VsuZ9zjEfRl2W+FVaV8SJlMpvRZkzC93N3SAZT9sng4Soe984Fyl0q8ZES6zQkXGQnfLOV8M8p4QGCUoDv0SrhwxBkm4UGEsdV8jKKcFzgC3Hc1/sL0GFWkviuC3EToswSG36h7LyuClwUbqwOL0mYi2dYpunj5/9WWQl2osQ4IwqZNuElMoJkmPdj6iBzAlxGBmmtjoh7t/DajNkxrrOHPns191C2qdgp7hWrU29KroJsKrvMIJJsYc5Hv6f5fbnd+U+b0dn5z5zYmfSFnLSJ2RE+V5jZu2A2UbcvXsAJucWe0vRhpz3Fy4CRHttFgNfM+jkcb5Hr+ekn2AR6xDAybX6nYWS3+fspIHELKf6vFKRxMryCd7JZN5sGbUdlPzv+ERL/m0nx280JFP8Z3pnxrvvmdXgRe3UM82ZoymT6KMYNw+Ylv1XXC/LU+V1WpsTEwtYR3DQxP1PlQ0/zh79jRh3NiAwSK8q8dMs2gux7mWcJ2knJaD8jtAx74uwjEszC3yXZT7Ym2U9EE1hqXnup3BV32/h/sHcl8FEWVzybTUggyAYBDV4EiDUY1OiiBoOyC5uwCxuIFQFFNBouFRUliyCHYEBJP1a8aLXVaj1aq7a21WqI1iZEQrgURTnEAw9wQiQEUcIh2f7fe/N9uxvCoYbSw/yUnW/mzZs315s3b968kaMx5r0yBKwxwaV4aW8qtWChmKVuKcVYm4MDpuPUs48yVY9Ym87vMBDgTR4ncF8jlF3pmLMPcrDVsj2kZT8shQ0HEMSxkq/trWjZy/6bn6wz5SHnHFNegbhygnokn0Q6u7dh/cnlxZtiRTgq3hNLxyFtVDyEEDlYWWqPwZ8kH9HDUNr+oViXBr/Vx/0Rs5FPbHtBq9yMP58SpFdG558bmX+Dmf+bR5rNv+jA/DmSHxx2/iKduSBXMh+Y//pFB+SPN/Mf5zfzv4izkoO/f3WXWd6HJrH1OQx/ZPQuNPMf96iZv++hyhsj8H7QV6bhf/fAIeDPt+Dnm/C3Hgo+Poy/VMO7DwX//mwT/kMTf/tDwT9jwsdb/VN9/yHgAxb8ShP+4UPB54Txv6rhxx8KvpMFf4pJf9ah4DfP0t5sGPRlGZfWeYXoCioExls8NTMmOKKC92h7HHP8YNuIy4pxzHFLMAXBCySYimCGBNMRTKUgu0EBZ5vIT/Tz+iLLT77BQi3WKX6eQ7n4d5PK4l+lMvFL3LFA2YfI8y2k5v+5HesEnaH57HrBcHEAbgkvtMuzswVEBcK8sHWz84qUqqb4WNjp5txI7PJs2YzMRXOVkQ4yOCgOaokx6gPs8xh8BIMHNPh5Aj7MAvcC3DVGPS/gWAJWsU5IDZ0jS57Oh9MoZJDMnZGZi+m3SU2SfFlWvlOi810Ske/TRWa+T1U28tHBHx6IgYSWSRqUM37BhCYWrwjVXAmmx5Ib4j8riayvV3AtXBRV3zvV1huwdX4dhRM6WB9Rzrvu4px/Vk9LfBbi6aGhGyT+lyg8TwxDsNY9K8XMJmmvgMlaJYnqzBJZrsnTNeqJnqc=
*/