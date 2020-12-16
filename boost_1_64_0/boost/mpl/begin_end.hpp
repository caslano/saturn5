
#ifndef BOOST_MPL_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_BEGIN_END_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/aux_/begin_end_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// agurt, 13/sep/02: switched from inheritance to typedef; MSVC is more
// happy this way (less ETI-related errors), and it doesn't affect 
// anything else
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct begin
{
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename begin_impl< tag_ >
        ::template apply< Sequence >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,begin,(Sequence))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct end
{
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename end_impl< tag_ >
        ::template apply< Sequence >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,end,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, begin)
BOOST_MPL_AUX_NA_SPEC(1, end)

}}

#endif // BOOST_MPL_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
PBSFsoX7EyTWQyewzESZKOYYFlRX/wuhs8+R5Rn1RtxzUxf3Rltwdq1v455/wqXL0L/5j6CSqMSfi2WJJe/93g9UdpBd1DPR6tnTOsfRSfKtVJkKHQ5TnWSi1Orek3oyBJJQIpDzHCCpCmTzoQok/UDUW9f/iWrSbr/i0BbOFTV5Lx06W5wG+MTbpDjffptX0DSbP4x2L9BHS+yVNhhyRWMz4T3WwXuGlWb4/6Ff6Sy2e/8t8FelYBWUAkfOPdx6zllfw70PD9u7PwFWIv5CB3ZMB4u5bPN2an9bkHH3v0iAddbjCIvtfVIoHPXNXO/a3mrP+sT4/3TRBXMNfOlDdAJ8/pwjrUon992e3HURzc1cXE1MVURovg4FtZEgx6pO2GgE0yvKScvJrnJ0IpmhzSXZlIesVIUhmmNz2uEyjhAPNCd0+JgnEd4EznzARK/gs0fKbj3lbgtd2vpTfTWt4u1A6aHwj0K1QGZehuN6mRgvVYwI3O5YeJ/fMxIDvoY4IYKEiCzfnJCNhGzhppyQg4QcJGRzQi4ScpGQEwu3kQRJ+OTuB99+ifgOSMR3EENoc33HJ8IbhuLJ878H3+dn3aUdEB1pV/ROsgodCbEwc30WD0RyRC1v+vg+CTtY8VKAh9NEFuUP4Do6jz1DLBWtf8/AEhJmj+hCeo7EisP4lK2rS05sbDY+5caKyZ67v/py91NfP61vgNY3CCVay3+85h+WQN8iIieS5P3uHd/ujXdPebBrv/6fQ/a506QrBtmNR/ivr45Oli/51l+FR7wQVh5xnpzN3jImN8BwxnQ252QGwBI8gGJQRksSCi+WwtGznBlvp6ajQoJ3MAvmc7MFSgD9Pwyz8/d/woIMl8/zBGJfhThUINY9L8YFXr8mpMUPsp8hGReu9jxMsIfGx6yxeZItxgvUQlnY2NMt+u0EuG9midR4BVqYYQTHLfk5TDP4pfWDnEPbKN3bu1cnnGSM3YT7sR5fpgxz2psqKpOKxmtFZVlJEbg3Df43OLit501CW9J5GPHQ4osMM+7ht33tF+ztKusjOGAJhhGOqdOi0OTZwvpzswpiW8Zgb9oNOI3TrKWdZEEJKfUO8A4QjHdYtfrRMJYjpHZvWGgfFsr/LVMFgi4JRq9+MHrtdz/Q7AKulYXdbLl29uzkh7HpFs/Zzz4/xRrv5m69TZ1iRzAAnB39pbv3OKYoyrzjCN8+3QvyGp2H5qFMrh4YsesDciPVfGn7DNhI/ojEti4s+4tvmZlN/NxvoEObpmcZW1dneaisx0V+4zW56WA85NWrdzjHQ5Rj7wH1kR4G2fQw570f8G8fMABhePwsJQHO6UGf7zlb9UZSktwdbv92F6s2RCfWLJCG28m7UQ6YoUaIUybMWIXvGq1kt9yroq+7kPNYfa1F5lx9rUfmTvpqI3MQr+5RThQplUR4Ma2J45lxEZtBGI504se4u9gzbnJ43ESIGkdyRaKRy53ZYttj2XJCTvN2ZCpTyyvY+UhWz+DPuP0vagPoJ26Su+gMiJMW0Yhk9oOaVuoDdIyjOGT2l/5Ez6SYF3Tj5nouGk4omrVouY6QAZ8ZmuzEyOihrzUofpAaUqtRT5PY73A/1U5YeGvIuR+0HfiOq8xf8r6SkXWcGtwuYu+qdxsGT8Fq8hqrT2wYYL39tgurB2DxAtJ2MePf9uf6f0ccez9UvEUpDmeMRokt7srQBf5mmZAs4HXMyyjtacWcrDORdb2TdZpkzSsJlZlZOJFS1D1lWqxoGpxopkkk+vTSEHySzofO1AWfzqcoE0dh9MDX6nwsA1MpNDL096ns23MISY74OJUA80dY7N9WV6apogpOpSssakzfIsPGAF8=
*/