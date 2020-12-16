 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/named_condition_any.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

typedef windows_named_condition_any windows_named_condition;

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

/* named_condition.hpp
fAHo3qALTH62I2J904OO2Y5MpOpo/Odene2YCCo2S73vAbom6CTQLUEng44F3RN0F9ApoJNA9watAK0Anc78Zr1l1jcy6JH1piGNYr317P8G0AzQA0H7gDaB9uf+N3wf18xyTmA5/ZAOYzkhyt8HdAfQMGg56Aqge5m8lK8/aA1oAeXMBpU1fUAPAc0FPQw0H/Ro8h0Lmgk6j/uUB98KvOUZTnlGUp5RlGd9yrMB5dmQ8mxBeTamPJtQnk0pz+aUZwvKs57Ig33Ks9B6H4wxQXlyka6gPHfSTu8FTQe9D7Q/9/O5vxroItDhoMsYV/sB2uuDoJtwfzPujwZtpf0uBt2J+cYzDvUU0KWg00EfBp3BONSzyEc94v2ktx7foNzvcHy8z7jXH3C++ZDxvT8CrQH9kvV9wvnuU9BDQD8DPQz0C9CjyXcs6Hug87hv4TfvJ85TOy/YcpeRb0+N3IPY/0W05yGc31YHNfmGguaDrgg6CLQYdBToSqAbkW9j0JVBy0BXoR2tCjoRdDXQyeSDPDKIFjrkWQGpkfJsRXlGU54xlGc85dmWcmxHOcZSjvGUYwfKsSPlGEc5dqIc4OM8w/cKoHtq5pkneF15GlTWhiNO9UXG/27jde05xu9+HnRH7u/E/YmgL4BOYj72B56fvfvja9rRd5ynv+c8/Qdxsz9wHPxIuZbT7n8C3Yh8G4P+AloG+ivt8TfK8zvoZPJZeGHeOxfEsaMW65kLcyn51DjnKxLfW0y5h4EWgo7kdXld0GLQlRk3HEmuM6tR7uGgm4OuzXE5ArSc+XYBXYfXm5EcT+tSrrujzyp8huqg7DdQrhnU50zQDND9qc9a0FVAZ4GWgJ4IuiZoBHQM6AGUo55yNIHuCXoox+9hvF85nON3LuhBoMeCHs7yjgBtxv/zQOcxjv0JoFfxPHxFBLfccmqqsRAJ+GUv3LILrwz8JjDL8fDK3ljlV776Z/HKL6CtHyN54ZZDHT2DXS7tiMUvh09LdWGYi09L/UtxzFM6ICf+Ho16vPHM4MP5KKa5+bTUHsU1Rzpisc0nY9/GN4PntNS/DON8Q8c/g3O+AW3qxDonj3NOgHFGfID4OOelqPN9pFBLqrEK0jikWqSTkW5AegHpV6Si01ONjZAmIDUinYV0O1Ib0udI4TMQnxtp9BkBDjrYgi3Ygi3Ygi3Ygi3Ygi3Ygi3Ygs3v9vfE/6+rmlVjov+7h/1fjdj+toEWtn/8VjuNqRgzfsKuCr5f+D4vwDvPQW6+7cfsBvxqzSyTdU3yjY7lQ+zjCWN2Hb/VOIsRWyF4jy/CO3nhNZsljaqYPr0znkBLrmH5r7T20mNwF9wg/isugfzE3S8Z5B13vzrFHcfgXci8UFfvZAmJL/5cx2d7xsRH3q7HxD+eeDlVxgxNTPwT8NOml5HxFiij3ucMebseb0FkRLmqjM2p+v5rvUYjo08c9fKB3v33eaobR/2eiaPW6aaLWOotonGyPWL/Z90odWkHg+GjnZMGeePFM9LcNrDBIHyzcNQtFkr/zRJvG0U+XzYa0/8lGkznNRr51sRPmVM+sU7K522fyNd1+yzR2GcJY9Rvg9QLaWukD0x8rFM+AclWY+ZEeZaMdbNULHqN5NncCzuNMl3YFxRox1k4Ss5n6fzlkNf2R2wKRfOKv7+V/3TwgEPj+8j8jGl+A/pkaTq+4WXjXJ7qM5pcTPMcVZ/QgSYWA2Sz8RuQl8fcawTM7+0xPzj072deb/EeL1Cme16YivHS5qivq2upROsJEZf/A+3qe6SPzPnHWU8E8ecZZ2ZWlsk7Vcapzn46FPu5TuzPvGzq/WJVXvrhTsUthdY2yCtjLyKdPc3oRzw=
*/