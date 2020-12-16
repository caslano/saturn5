/*
 [auto_generated]
 boost/numeric/odeint/util/unwrap_reference.hpp

 [begin_description]
 unwrap_reference
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_UNWRAP_REFERENCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_UNWRAP_REFERENCE_HPP_INCLUDED


#include <boost/numeric/odeint/config.hpp>


#if BOOST_NUMERIC_ODEINT_CXX11
#include <functional>
#else
#include <boost/ref.hpp>
#endif

namespace boost {

#if BOOST_NUMERIC_ODEINT_CXX11
template<typename T> class reference_wrapper;

template<typename T> struct unwrap_reference;
#endif

namespace numeric {
namespace odeint {


#if BOOST_NUMERIC_ODEINT_CXX11

template<typename T>
struct unwrap_reference
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< std::reference_wrapper<T> >
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< boost::reference_wrapper<T> >
{
    typedef typename boost::unwrap_reference<T>::type type;
};

#else

using ::boost::unwrap_reference;

#endif

namespace detail
{

#if BOOST_NUMERIC_ODEINT_CXX11

using ::std::ref;

#else

using ::boost::ref;

#endif
}

}
}
}



/*
 * 
 * the following is the suggested way, but unfortunately it does not work with all compilers.
 */

/*

#include <boost/config.hpp>


#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <boost/ref.hpp>
#else
#include <functional>
#endif



namespace boost {
namespace numeric {
namespace odeint {


#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL

template<typename T>
struct unwrap_reference
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< std::reference_wrapper<T> >
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< boost::reference_wrapper<T> >
{
    typedef typename boost::unwrap_reference<T>::type type;
};

#else

using ::boost::unwrap_reference;

#endif

}
}
}

namespace boost {
namespace numeric {
namespace odeint {  
namespace detail {


#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL

using ::std::ref;

#else

using ::boost::ref;

#endif


}
}
}
}

*/

#endif // BOOST_NUMERIC_ODEINT_UTIL_UNWRAP_REFERENCE_HPP_INCLUDED

/* unwrap_reference.hpp
MSPTucTIdJ7GyNSfGJlSNEam7sTI5JCMTP4Eftyqs/RLvo/xjFFzsiANePMZnmtqSJ4chhrjEWGXfB4VvXDUjseR8QrL1v32blvhMGuOrvy3w/e/nMz/iXUHZ316bayG72aXKEQIz6aD8SJQMFzBRXbIlAcXJZr0E7TfTi7Jt36HBeP8YnC/he8QqlbDC0++evcquBDmCr5nhuAAPF7IR4Rm0Pu+dCbOvm0FldQj+7ZV9De+pshZ450fXISF3xFctNiEVyN3O8ueKTVRM7D+JwYXKUiGwOAzIAJjGCHuPLERFMVnLaBfpZkcE5vx1wmxKvxxQe4q+IxZ/TS4m2KTEQunDU4I1A4O34T3XrFRDCqVaMZhbp/lMeqb4zLIlCLzbnvwWdDX1ZeCz+Sk4fG1l9Sn1WfKdhLUp1nUyxTHRPgoP1oUWv4Q8iMwtG6dhcUuZ2Kh6MQX/nY/TX6dBJzxmUT+l4QYkY/e5WdRel8hvyoEuKG/KTVb6CrKI1U1+GjVZcJAq3XhpVAK97kVytX3GNy/v6TbzMzZuEmiXZiLI0+85pHKDRJM8kJXeTMuskFU8Fasaz3822dmg4bXsOp2VPIIzAMwW6yWb6XkK3brUb6Men/pc03//Wcd7lKSXgdmGnnf5pQ3E8HiLJCFHibY/hWxWGoP8V2Rqh6lS6BzjvmvC5YUm3C1u5Wf3usBzbED+uocSZeolciEQtJN/gs0lSHdk0+EZbAMMO7LSPeilia7F5VgOwzyU2ngAvDAnS9z4HVIkjEfQ1JeeWMg7ovdr/d8vIfn0XSLFDkoYyJe+fv2NIh87f3tvWqVdkdjl3c0LcDzpFoIuvnKvpsVDpZfpV2S5eJv9t0pFFYxmkUckrUYoip6xFnQ48Lok9mxsr8Urj+bqL9dZDi9+yo1SiRWm4ZZxpgdzHxUIP5whNB1UCBTlWnOCJK/SiJ6t37CH/Yg6+E1hzdRnWIzAgnQ1UMFwo/suHW5GX8k+yypwqZyf4QQn/Bj4DxibA8avvRf4/pJYHe7xiNWuk6Er8FV3yROtTGRUFgoQfDAy1qIFqUqfr01fBmrN+jEIW5QS0p40zweBYUpkuE9dOmRmFmP5SqvuUC8dph7PbNi79KuTVU0apN4CqkNnbly+U5/4UEESZpHX08I41Hui7rCELd+bGbtOe9jcJUH9BivWIhwUNy+Xp9A9WQ6+oIivYB4B3SidPtZ9Kd5cc14k7zCj5nfq7pihSrtBsv2HLiRUzCU0YlkXtZdNLK9/AfvRIuj/TVt/fkFGvzjKjgMTaoz0lyBEcrt1ONtu1gZbpX81L2456588QMnT1vtgfjZuKLwMoWzKM4k8ccQVl+cfkYqq41SbtJLee4jMxNVPcpXFG4R53OxqQfpDlrcBThUm0mlR6XkjE1Uf2aD7o5bAZF4N5jo1PlquliGZPQGsL1siS6TVJP43PW0fG0N7rCVLUnh0IlbPfmiBwEzkaPD0G2BLNnF9gVn0YOsF+ULV3fECQwZTsbDiTtyEi7Z3MX2orfzhcMhtYqJWfniJkdsj4PHT4AL5hG9f4pKC4ZDWW8EkMCT3ufXP+SRQ6WK8zm6MlOS8Ycuwj3KIRqFeJH+EYNVyy92/bt/PnVsGt73qwjL9T8/c2/2gHQEOCpvoYXDm/lh4VDuUnjUCLEIChwzD2PAsv0j7AsudJyZg485wlY4XEtxSPiQgoPOl0H+QzYxAWG5WEfcyFT0fGGGFjPCJs5DjKx/Al3Vbk90c91FK2bNLLyAk/lEHNIgsikOyeSVX1y65vommh40+R98UfBCSJ7w57EmYw5kqIe8oOSTRxTQ3YmYgaolD5AHK3KPwnHy2y6nj90FM4M=
*/