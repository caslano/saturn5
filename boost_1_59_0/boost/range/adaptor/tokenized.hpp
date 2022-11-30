// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_TOKENIZED_HPP
#define BOOST_RANGE_ADAPTOR_TOKENIZED_HPP

#include <boost/regex.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost
{
    namespace range_detail
    {

        template< class R >
        struct tokenized_range : 
            public boost::iterator_range< 
                      boost::regex_token_iterator< 
                          BOOST_DEDUCED_TYPENAME range_iterator<R>::type 
                                              >
                                         >
        {
        private:
            typedef           
                boost::regex_token_iterator< 
                          BOOST_DEDUCED_TYPENAME range_iterator<R>::type 
                                            >
                regex_iter;
            
            typedef BOOST_DEDUCED_TYPENAME regex_iter::regex_type 
                regex_type;
        
            typedef boost::iterator_range<regex_iter> 
                base;

        public:
            template< class Regex, class Submatch, class Flag >
            tokenized_range( R& r, const Regex& re, const Submatch& sub, Flag f )
              : base( regex_iter( boost::begin(r), boost::end(r), 
                                  regex_type(re), sub, f ),
                      regex_iter() )
            { }
        };

        template< class T, class U, class V >
        struct regex_holder
        {
            T  re;
            U  sub;
            V  f;

            regex_holder( const T& rex, const U& subm, V flag ) :
                re(rex), sub(subm), f(flag)
            { }
        private:
            // Not assignable
            void operator=(const regex_holder&);
        };

        struct regex_forwarder
        {           
            template< class Regex >
            regex_holder<Regex,int,regex_constants::match_flag_type>
            operator()( const Regex& re, 
                        int submatch = 0,    
                        regex_constants::match_flag_type f = 
                            regex_constants::match_default ) const
            {
                return regex_holder<Regex,int,
                           regex_constants::match_flag_type>( re, submatch, f );
            }
             
            template< class Regex, class Submatch >
            regex_holder<Regex,Submatch,regex_constants::match_flag_type> 
            operator()( const Regex& re, 
                        const Submatch& sub, 
                        regex_constants::match_flag_type f = 
                            regex_constants::match_default ) const
            {
                return regex_holder<Regex,Submatch,
                           regex_constants::match_flag_type>( re, sub, f ); 
            }
        };
        
        template< class BidirectionalRng, class R, class S, class F >
        inline tokenized_range<BidirectionalRng> 
        operator|( BidirectionalRng& r, 
                   const regex_holder<R,S,F>& f )
        {
            return tokenized_range<BidirectionalRng>( r, f.re, f.sub, f.f );   
        }

        template< class BidirectionalRng, class R, class S, class F  >
        inline tokenized_range<const BidirectionalRng> 
        operator|( const BidirectionalRng& r, 
                   const regex_holder<R,S,F>& f )
        {
            return tokenized_range<const BidirectionalRng>( r, f.re, f.sub, f.f );
        }
        
    } // 'range_detail'

    using range_detail::tokenized_range;

    namespace adaptors
    { 
        namespace
        {
            const range_detail::regex_forwarder tokenized = 
                    range_detail::regex_forwarder();
        }
        
        template<class BidirectionalRange, class Regex, class Submatch, class Flag>
        inline tokenized_range<BidirectionalRange>
        tokenize(BidirectionalRange& rng, const Regex& reg, const Submatch& sub, Flag f)
        {
            return tokenized_range<BidirectionalRange>(rng, reg, sub, f);
        }
        
        template<class BidirectionalRange, class Regex, class Submatch, class Flag>
        inline tokenized_range<const BidirectionalRange>
        tokenize(const BidirectionalRange& rng, const Regex& reg, const Submatch& sub, Flag f)
        {
            return tokenized_range<const BidirectionalRange>(rng, reg, sub, f);
        }
    } // 'adaptors'
    
}

#endif

/* tokenized.hpp
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
*/