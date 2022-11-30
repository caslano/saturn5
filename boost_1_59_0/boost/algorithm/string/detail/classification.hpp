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
#include <cstring>
#include <functional>
#include <locale>

#include <boost/range/begin.hpp>
#include <boost/range/distance.hpp>
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

                #if defined(BOOST_BORLANDC) && (BOOST_BORLANDC >= 0x560) && (BOOST_BORLANDC <= 0x582) && !defined(_USE_OLD_RW_STL)
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
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
*/