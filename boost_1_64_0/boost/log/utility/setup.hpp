/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   setup.hpp
 * \author Andrey Semashev
 * \date   16.02.2013
 *
 * This header includes all library setup helpers.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_HPP_INCLUDED_

#include <boost/log/detail/setup_config.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <boost/log/utility/setup/from_settings.hpp>
#include <boost/log/utility/setup/from_stream.hpp>

#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/utility/setup/settings_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_UTILITY_SETUP_HPP_INCLUDED_

/* setup.hpp
JJgClgI7gp3BLmB38CkwDewK9gS7gfwe4AgQdrhv3kdOJI674r7FYK6L+2KKhN93FGgE14K+4FiwHAhLXh8ngLXBiWBDcJIYL00Bk8GpYGdwGpgOTgd7gjPBQeAscAw4G5wMzgGng/PAZ8FscAU4H1wLPgtuBJ8D3wGXgh+Bz4MnweXgWXAF+BO4ErwKvgBeA1eDd4Q+KJ+PPHs4qtb//vnDOHsYZxA/3vnDf+bs4cc9d1icOfzY5w0n4+zgfjDTYTbAHIA5DXMHJvSggVSDSYbpd7DojOGiq+gquoquoqvoKrqKrqKr6Mp//bvO/8/I+Ged/59sw7y4WIPMZkT/Hr0m5o/2YfIp8lDed/pwY8jcviOvf/MymbvpzM+2L4UVsCaev0WLsAp+izZVPw+xDLcbgR2iUTh9uJiHNUhP/tN4HEJhV4HbjcM8l4J08SNPwXhYf0QYhX+D9iVub3CzT8UHSXuSvPdforn9WFId/zeB6SXCQnxwDe2f5RZWLe5WFr8pqcd/a/q3BW8HY361OAyMt+3BbwsaBT1/c3hwge/c6mt/+K2fy6Dn74Fcj2JdxhvmdZG/H+n5izXm/Pmrr8uyw/ydd+yUr6S/25PIZcVxT9Xz91gfzGs9r77hdqtIW+TROOTXFE/fIPYYRppeXj7ndhuQzyaUmkh97bnz4YevPX/0QN7zMq3r+SW3z0IZjBUySprx8KJIaD5/KBH4v3A3/VPzvpdvBn/nYZsfWlYuwp6/ZyDKynX+uzsJw0xsOMqLAjcbS/Ayk1dewH9tmXlDI7hwXxg/mA28zMAcziszw5CA+cqMrk/KEXF2isjzC9xPNNJI9lheEGbB8qLny0Fu1xLlj/L1ci/dfVW38uIpjDR9bf99bjcf892Mh2HU3VfUwxAy93MncIlzJ0RcgrhebfQzLtB+6PahYDC3j3MrBxm9exCi15tvefgj0U5K7mWl9wC3slCGh+Gnl53vuJ9gvWxU5/bFUY8D9PS4xt0ML7i3QQ+jJvejFCyfIkzUSe4/Dm14CT19fuKyZwruedDDrHsk7xxR/NbjVQ0pHOr+TmHq4MFP63tMSnA38Q+tB58fzt9mfsV/S3nfyuZ14P1S5LH3SfyZcr9QTHcdF+F+IMr9qiN6uUdjWaCtFOXsAnczCbnnsZwjDA99oCg7O7ldIv/qTWMYkbfCT4RbWfcUTpqehvdEvuTl08v8t7enNlEPx6znV9rAwYMHjsAfep4Fvcfj5bHMB4He3D7VY50JBSm371uwTuht+T4eh62kJN+lxR5aLyJ4OBbEVbyrwv05sSvHW68bMdxNSd7L5qXf69zdzofWjSrv5aUvfuthOBCTiIL1RT8H5i0e5ktYr/eGyzR9D+MhLt/oqc5wf3V52Io+BsDiES/TH5TiZyc99nveT1Ku/13fFn6e7+sZdajThFqBHVa/cmtmlRs5n3f45+27Kfq28H/228J8XVSMod2/62uB2SkKqR9f8od/t30tgWAxMASMBMPAkmAEWAosBpYFK4DlwDiwPNgIrAk2Ae1gAhgDpgh5G7Ai2BOMBgcK++HCfgRYFZwKVgNnC/kv4FV9PIh8F3pEwJwVeiwWeqwV8d4g4r1RxHuTiPdmsAS4BSwD7gbLgW+D0eA+sDH4Ltga3A+mggfFuvoxMAv8ABwE5oj4bwdHgq+Cc8A9YLZw9yy4F1wk/C8X8hXgYXAL+B64S9i/Lux/AffoYxzoIvQO4vHHJdb9KdgIDBLr+sFgUzBUrO+Hg/FC/wQwCkwS+dVL6NseTAM7iHzpKPTrDA4T66ijxDrqGLA7OA9MB58HM8HVYE9wgwhXlD/RZ6F/9lD++sGdARwGFgeHi3w=
*/