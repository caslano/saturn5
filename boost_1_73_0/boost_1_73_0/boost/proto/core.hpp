///////////////////////////////////////////////////////////////////////////////
/// \file core.hpp
/// Includes the core of Proto. Not included are the contexts, transforms and
/// debugging utilities.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_CORE_HPP_EAN_04_01_2005
#define BOOST_PROTO_CORE_HPP_EAN_04_01_2005

#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/eval.hpp>
#include <boost/proto/expr.hpp>
#include <boost/proto/repeat.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/fusion.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/literal.hpp>
#include <boost/proto/generate.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/deep_copy.hpp>
#include <boost/proto/make_expr.hpp>

#endif

/* core.hpp
AB8ACQAAAAAAAQAAAAAA8WY4AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1NjhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSxu2lZZcBAAASAwAAHwAJAAAAAAABAAAAAADNaTgAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU2OVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLGo68uxQEAANsCAAAeAAkAAAAAAAEAAAAAAKprOABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSSvqMaZwBAAANAwAAHwAJAAAAAAABAAAAAAC0bTgAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU3MFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIJNwqYzQEAAIcDAAAeAAkAAAAAAAEAAAAAAJZvOABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNThVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pStYy48Y4DAADbBwAAHgAJAAAAAAABAAAAAACocTgAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU5VVQFAAG2SCRgUEsBAgAA
*/