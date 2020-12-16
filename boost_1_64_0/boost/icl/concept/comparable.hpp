/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Equivalences and Orderings<Comparable>
//==============================================================================
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator != (const Type& left, const Type& right)
{ return !(left == right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator > (const Type& left, const Type& right)
{ return right < left; }

/** Partial ordering which is induced by Compare */
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator <= (const Type& left, const Type& right)
{ return !(left > right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator >= (const Type& left, const Type& right)
{ return !(left < right); }

}} // namespace boost icl

#endif



/* comparable.hpp
hmH3g3oDwtNfheXupCxUk4/2y4T+9OSMfUvutGWGEwk1/g/HPdGP5fLCut91J6l6tffamvjq7VtYaZhOc4W2yvvwG3Wdb3/csKTQIAKPmuu4rrtYr9CgUhKhFq1gLMv1SIyS9WtmPZ3/NtFuqZ3Kz8vmcTPkEdc149pU09BaZF7xI4eu1NSaXDx7+6BXheKr1KHBAU1LOPjntJu+aoldnlsw/JZdEfR6Am62dmwqeMeJnPPmKXEnQrsx2/Yit5LpWXHszk11va395Mzn7ORc3KPrM7widKl1qoSPdARee3zquFqY52pvEHG3+y3frcEIqY/cNVdbTB5F4dVtawo/8+rk28Ymye8UiLSra1oYXOF5GtGEd+jmhq/BvODa6xzxPGrjvG5nwJTDI5uoPAozvaw9gwNBNGZY1vz4G3Fb3Y5v63KWu0sdfln/p2cUMgNuUQ+osa0FO1JNjs5zzKj5yhbgp+D9cs1HYoPbzt8lcEWFrTdK0WKo67K0ygLnuzOmrb2FShKTdTP181HG1ealL+Pmh95eIcAtyPDC4v52X5LieRs5/a++j0yRhdSWqw2pZnL71+vdueOGZZ1O03KxMFyRTGqBfORnPVwp5tT++NRmnpk6+RBc+s8al+y5UoYdTmyVgpUyaU+vfZn8KONY+9J7gopa+ypupEMJGa3tHYubrZoPLnDjL4tyrcRvln2mePltUPcwISfjpnbvLYvjgGQ/3F9ebNMQdbloNYyF/yZr4Bz5Qnbe5LfZoP6rVskKMU6/Osd9U9vFWfWRoKihKotAtiGtgETC9E4bVjz7DV7szLfe3iniOImqRo2HB5LnSvZctuMtuBw+MEg0ydN3XCquGqj5zr3XcgmHxrLKUUXiWZwWVjxzlU9Bf69lzUsTGxFSSom2Bj6vliyRb3jkR2nqZm0xA0915/fdNK8N19IWmh4lbd92XX6qocPTq5uqXWKmsviI5qKC977vXVI3v61trbHYLb4cKaHo5I/9lDPVDWoHkkybUhIvG1vabrbqKr26HK1+f6D81+xdCXxM1xr/bgyJfULs2xTRUEtEal9ChCAICYISk8wkmUpmJjOTEGvsD/VQlD6Kh7aqrWpLqapSVN+zq+XVrrVTW6mles/7z7l35t47E5W+7fe2M/nynfN939m/853vnrn3zuRJ+38oe+LErGm781bcvVLt3Pwetuw5K2f0WFA6vOJ3T9jpzz4/cf3tBfmmFzc+nD6iWrntl6hi3TIbrjQsuu7AO8HBTRZcLPH65RuuQ1PnVZ/XqUHwhO9zW99q9OGT06dbfHjmD2ca7ihVor69ytao4ssnl21d97MDLQ6tv53Xa/0vPyzVDfljhZIZTUvHDjrz2cxOP7yR1vTKjd2XF8zuUK3KWUfpZvk5fToFzn+8b+xLqVlb3zU9F7WmxBHh4z8fuhywtsaAhBUTm466cXp1uSHN1vxyJdpW6UiXn7NrzynX8sgf5u9/39J1U8pfBr/W7+CPE9MX/pzWq+SmCsu7Dq5hO/dL3Kadv//S6rgy4MnIUabOQ6a+Pu/ozGFFyhgyf0o+1WollRxy94PUtRHHZo4r9Yre3i3+m890ZxfVb3Cv1KK597IWJ5wetzR2ytxigeP2JDW+5WrzIWvSd29Q18P7nh9XffBz11d9d/hO25aj1lepnNu7U6thU168fKbSG5devP786J8++NOm+5ub70vfWfxD/fTto7+ocf5h1X3Fgr6yZyc2G9poULczR4od/MrU8KttWz4ufbBd5OzZ9k7Vjo4om9K73heHN9VdunF7BVPom116XTz+cNiEFu3f3Ldg5JsVlkz53cKYS8m7R+8otTnw5Lsrc4vVXFx7/Og=
*/