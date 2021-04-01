
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
4BkCGdx8DatfxX7PKbvySnGNqnn5Mh4ceWR4/zqoONy+/Fffd4QP4sJyDCRXuzQDwKUOuxPheJOaoA1vFW6OGLw3dNBDJ3BdR4lIFvCzRHtpCZzTFEc/2t1S+vejeGNk1YfNcq5a4CHKP3l57hQbobngLgP01jn7KTjUydk9FE3PWTKLG5Vsx7je1v4o3Ih0fnW2d7k4wrp/Y0PRWC/YChGmH//RCOYdbfthy5stZU6ER9IONPPbpMTSkRgGxSFJZo7zpkHmObC0kT3KPQdOc4+WW93u+QgPMFe+CrkWPgc9gHyCyCPA4g2Nu6rCdb4xXXXtPsxaGN3tHZL4p3mZaIxeBJB5VlN33QiW504LTpmgfAbzyEmPsiRFB+mYY08RzRpo/6R5CAzp6YqstPgpeu2dyl22hrgnMpIMHMLlS4YlWoQtT4uLIOon71v0cCNf1XfLxb4UZgchiPA4zzpxHzfeMX5iux3FoMyuxX5H95iq0t88NsrrzlyQBOxWcOvDvkyrJZx+NP0HpL/XnmH/33LA2mKZ3mCl5yiH2mAurfyhrpFxxMeYWfQDQw==
*/