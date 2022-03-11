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
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
*/