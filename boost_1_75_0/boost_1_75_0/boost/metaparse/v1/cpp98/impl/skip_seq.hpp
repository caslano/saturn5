#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct skip_seq
        {
        private:
          template <class ParsingResult, class NewResultValue>
          struct change_result :
            accept<
              NewResultValue,
              typename get_remaining<ParsingResult>::type,
              typename get_position<ParsingResult>::type
            >
          {};
        
          template <class Result, class P>
          struct apply_unchecked :
            boost::mpl::eval_if<
              typename is_error<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >
              >::type,
              typename P::template apply<
                typename get_remaining<Result>::type,
                typename get_position<Result>::type
              >,
              change_result<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >,
                typename get_result<Result>::type
              >
            >
          {};
          
        public:
          template <class Result, class P>
          struct apply :
            boost::mpl::eval_if<
              is_error<Result>,
              Result,
              apply_unchecked<Result, P>
            >
          {};
        };
      }
    }
  }
}

#endif


/* skip_seq.hpp
6Tk9uunnGb0R3TeXRvL1G4TvmKe7w9ezVMP30t5d8b2w6jzx3fgF4XtqTCS++ZUh+L6h4rtz5bnwPfxFJL6PmrrB19ML8f10CcNX42n6iDJk0lPB/CkhGIlrzodn2z8nns0YE8mzyypCePYNlWcNHJ0gnw7tgsJXsd3w6dlqWvZwSJ2O6TLPOIz5lZ7A3rtMR8sSG6sepy+Dlnn3SkzUccadhzTExbChLN3QX59gEMGVYbifCN7xqe+MRGh9F3e/geiuxRpDmJOAviH7DBuDVIyqVDfqXIb5cKZj0T6AmgN7wo/ADmbA1geB/e4JnPSbAF6h9D10DHhPKWwDj71sp3u+tm/nBzA4npfnfEb7dt4ZTft2nrf6b9TT9UPEUa4KbFrDadkTfN9Ohegr+ApsnA9D9+18xfbtPC+fwn71GbA9On/0M4o8uQw76KIYrWP4rkJGhp4CsplzEc+pRHxWtZ78GujEB1b7EYkdwWctX5wPnz3xKfFZ7ahIPuv3Oeez0C8hq73gD993Vf1p+L6rQmO3bNZlHFjOC76jnxB8g7vA9/Bn3ewJ+wMz/gDHZYbAlxoBX2V0N/DJRx/pVFZu4YF0b38eDKRTEyFIm+BsVNV1ffCYpTeghXy20jG9mixa3FUMEyAIuxuRA9XIOjsVkdhQWKvu41eZmWceGfm5xsxdBBznxZ8/JvHWP5c2fT/PNr8+L88F5NSPAs9V
*/