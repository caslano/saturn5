#ifndef BOOST_ARCHIVE_DETAIL_AUTO_LINK_WARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_AUTO_LINK_WARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//  auto_link_warchive.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

//  enable automatic library variant selection  ------------------------------//

#include <boost/archive/detail/decl.hpp>

#if !defined(BOOST_WARCHIVE_SOURCE) \
&& !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SERIALIZATION_NO_LIB)

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_wserialization
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

/* auto_link_warchive.hpp
vxUZ4e+i1Q9RkflgspmM9jNZuSyRER6hCydzzNPZ8FI8Zj59ts6ekZfo0mPWXDawsjl7HODEL4PjCCuXYY88XXrMvPBNnT0j57OyBY+Z0/6ks2dkM7XOntkgx8oVWLkWK5dhbShWLs/KDurC9Ovh8GNlM1YO4qRfA0eoLj4jH5Hr7MlcdjQbbs7KCk78BvRzly4+I2cSmVnHqEOXLyuXZeUVnPxVo8tTF5+RcznpV6fLUxfOyPm69Bm5gCPXJQ1PVz5ELqcpPH9VuvxYuRIr2xC5cCOiMyuXYmUXncyshblzZFO0MC9dfEYO4oSb4L9QXTgjR3PyUxqygiOXgZzGkctCnsyRzSDPJzLbNiAv0V0vI/83O5+QkCDub753MPmNmSIed7aIHxzZFZ7uN+a8I/h+jBwS6MfjTjmxU3Ha3zy9KXLduaHXySGIjIMfwZk38wmkJeLrtCTN4MDufEwABTFanY7k27stfXBCmL4pnDOO8ukaqvWL2HUPDA/ELCqjK5SZQJpL6CO8dRaGevyOaOdIHxwL6PhB/Ah+T50ugCwJSJksMeVArpMUa6AvG0sn6+KF87tFYlMRTkN+44jg8XuG0kdQoG9gBLl+XBsOncyWbY8wb+aa2bh6MjeclLdO9g8J66r1vUmKJVmHYhYsuDsjcJcgS+Le4b6BgfA78XvS5wkKDGcS9cWozaPIOIaR/ALDSng+ZtnLmLO2c3ThzkTMTyZ8Mvclzv0mm9VvgK+7T3HuJwdY/VXWf6C1Z8MLiAyXwviWrE+xvgPxdf0b049x+j/SD3P6Vy/WPlSrp8/DuV/1pMM5/Xu89jysnEJk5n7wd3shfogvXU8Up0ETTrkahn3Kjx/uGxYYGhESpo3bM4IfFuxN+pcwPvGJc6dnMylHR08un0xq3PA2COfKznpyW08dt378EC5grAtAI+7E4YfthxhZl45TBzodeijqir0b9JATPhz5nUT1wcIt1Y9o6AcXVoZE1kOlXJmkB9FTy5G3HxXG940MCw8MCUbxhEZ0Mi9StvQDJ8ZduidxNtS6rVREr/eLPKztsHAcL/WwxrwV/nWGp4ttGC6RxVLccPaxBsPhODJLT4/uMbMGY5yI41zpjDKVWChzbgau1hqi7wNoKb/IrqH9XIlMttPA2dFtzoGNx7lpEFnvZuHah8cjpUU4YAa8tryS9ytR9AOTHud2tPPhBwQGU9YqIpgX6vnBflwt8zwmIJPpiaK2WtnOqS15vUEnt3FxLiK3dXTSyXFy9FBtnB0d7To4c8bthfYkj4r2ZHRP2gk9byegJ7lap9jRs/3t7UiAkXBuaCU2w/R0v113POHAwJVCqbAbCXyZB2m7CAzLXQsfvVvjOQOPCYU7HvAcJVfLsVrk0dhapXsIaawzwEOoEE8kHo1ZubGb7undozFdcNYqRCQnJS6CfkbE/2hL4a3pzFHMGbUPUMSWWz/EFWpRHTqN4XVwssjmkKLXEDwaa4sVmdG7fqVApsJMvB2f5ciVihGoxO2cOdng2vtJVAq5SqImxSlQqwXC+EToC8sjFrtuDc+J1PTzz70qej49SSxF8xXZkekWnaOvB0qlWCiWKNQGep2xELt+VXbMTh6mv0lUKFGk+glqMzXIML/WusIxLFcSjVykNh7R2NFPdR7WKk574aRVwnIuUtJaQcjG0z426rdQrb1uqug3vOjaxG+5MbRSk2v/dbp0Cfw6PSbUeHnSSzetMU8tkVUyB6kcVxiibf+8Is5cz/H0nIWe0w930HP64e31HO+P+le5/j4wso7Krvr8QTr0qmTRhGgNNyFMcdF7enGoyF6OWKkgDk0H84REA5+ZMWvFzKiSASFZw8Ev0kQ=
*/