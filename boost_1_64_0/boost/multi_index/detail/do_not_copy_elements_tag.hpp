/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_DO_NOT_COPY_ELEMENTS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_DO_NOT_COPY_ELEMENTS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Used to mark a special ctor variant that copies the internal objects of
 * a container but not its elements.
 */

struct do_not_copy_elements_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* do_not_copy_elements_tag.hpp
bgMCI66INbxG2V/HNRentNsjKEzZhKVFd7JUgChTi7RP7K/pH+RysNPvcvkG1bLwufPoy/xzizs76t8zl1KWwPpHTTBquRk7Tftq4iBEKfAW6YGlMm9N4ocH9eBQSKhHncdThOLflVD58cfxuwo3ncIKxnAyVtNBvIdVqYBt3M/zdNlg2+kxJvF6xqcVyDelXT7WmyahUBS4gc/PK9yIVkQ45xE3sJknoKaxYeF0xDHPOhp46xOiuLFs9dYJPC4Ykim/04hkYgKFNNpqLR3s/7HT2CV12wLBxitDVGGJtoDsVbCcgjtHgFXwQ5It+4v1QqjkCCncSiM2mvI3BuVWBZxuN4McuwMQGwTURmiioKwahxWPtJovK9tuNgp+B9KrFeEZQU3FM0BxJ6iTIximcJVey63Y9Bq+qVjzLiMzIgC5pcUH9NLa7VqTDwbhB4Troro3oZACan2vBOLasrjxglXXLFwvDq6OkGAuRa50z92uuWd/jbJPuS5537/LKR6/RkHcrpPaKGP+NsrAdPn1mFF9a1YZhNmDpD4BKQssEMSIbnqzQSr+oe+h3w==
*/