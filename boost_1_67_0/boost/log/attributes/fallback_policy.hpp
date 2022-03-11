/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fallback_policy.hpp
 * \author Andrey Semashev
 * \date   18.08.2012
 *
 * The header contains definition of fallback policies when attribute value visitation or extraction fails.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The \c fallback_to_none policy results in returning an empty value reference if the attribute value cannot be extracted.
 */
struct fallback_to_none
{
    enum { guaranteed_result = false };

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const&)
    {
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
    }
};

/*!
 * The \c fallback_to_throw policy results in throwing an exception if the attribute value cannot be extracted.
 */
struct fallback_to_throw
{
    enum { guaranteed_result = true };

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const& t)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(invalid_type, "Attribute value has incompatible type", (t));
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
        BOOST_LOG_THROW_DESCR(missing_value, "Attribute value not found");
    }
};

/*!
 * The \c fallback_to_default policy results in a default value if the attribute value cannot be extracted.
 */
template< typename DefaultT >
struct fallback_to_default
{
    enum { guaranteed_result = true };

    //! Default value type
    typedef typename remove_cv< typename remove_reference< DefaultT >::type >::type default_type;

    /*!
     * Default constructor.
     */
    fallback_to_default() : m_default()
    {
    }

    /*!
     * Initializing constructor.
     */
    explicit fallback_to_default(default_type const& def_val) : m_default(def_val)
    {
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    bool apply_default(FunT& fun) const
    {
        fun(m_default);
        return true;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    bool apply_default(FunT const& fun) const
    {
        fun(m_default);
        return true;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const&)
    {
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
    }

private:
    //! Default value
    DefaultT m_default;
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_

/* fallback_policy.hpp
LxJIs9Q+o5Mt7PuwGKMiV5p5zjiFytXp/gQIzeJnZrDp2znZTivEQkc99L2Zz31cDEYFnkiS9Te/5VU6NxH23XqZaeTfiMprlFChdgY+stpNrYUTzuge2Qres49a6VRTBi4bCde5ksBrAnsFqcey+VpdRZ4Y6b2G3oLTJcuuZSMy/3/zA4t93QvdmLI9A1wjqNxNuG0N5FaAKPOmSmltJaraLfQdy/PIpffVyj53n3E53f+sBrHjpn2a3PF89+ZQXp9jaaEVo5ZIYT1y2tESv0ggxrr7MRWdWt3yfFY8HiyyAKOdhyyI7qpFziI20qR1h3+njXJnePgnzwuxgrmwXaPoEK72WOOuQ3JGM4/zBZqSrLSgz2gtKf0J6Z+T+eNcmVWibkoHoOcOR5OOaxmi7QSlMm2NcI0Y0L7MCMBRv6m9Kr3BsvjgeYTnA4MZJQCXMq2q04339NNrVbiTWA8TZsJdH/dzZzevlLyV97K/iPwTo1tH1n96GD9XIRqNrRdqz2ThufL4/Y6Cb6GRPgd6vj+DYZuFIbdTHbdT+Vihv3On56YhO6RV5CEQTmckVDX4cKx09DovCYb06Ty9yOYzrkb7uI9TqJWvffRuzFHGiSrTnCOGBVGS8UAEIhY+O0cw7e43X9IsA+hr5peNjATWvdulhNNV966OO2FfQdJ/DjZFKikHFCWiH0odKbmprX3qL+xYvscK+y1Y7wH9OHw06cVVABSx2eK6hj5XXafXMTy0GWgbPqOfG+A7S9mF+T7b8iu6ya99/DLOpBcrcj/yGW/kBvDxLw1BZs2bjwbJDwQ363qTTz6U4+a5CQsAfTCouXoPnGvyDN2Gj4tK3pmjSnOhb/SNLnAkVJABqcybNzqPiWrCAMISN9sy0+ZvYWkIjbawFd9kUszdDzQcpBauQt3Mb1kgxcHcFnOudRLNO3NVZnMF0qeU/FOWOGreQaOQXbarNK4L0UvWqpIby32Op5b6sCbaPX+TtcjHogitRgFkpopm3CIQgQHTrlp8pEcs2ec2XE7EiUNgv3eYm/wsGkux0ooWqAVFfKW30KhJLMluDmguTLLKsgt6QBcaYDPuY0Z25bcW+YVq23gQ7EOSeTIFjWVEe7AKbft2IrKdug6jNcia6aUZi3B/+c9cZsdb/XWmR32mWsAMTjtZGowTj39NnMDMU7PbdVSgcsGqwYAi45Gc12SPpY8GEC6KM8WKx6xp2KOY8NPR+TsTe5mn3FO+quDxDkBNsxOXUk7Mds22CxlRe9K41kxtI59Ynz7ecGtZU0jJ02kV14e3fpuY9memOXptIp99CtBH52197ci3yEjyyNXm9MJqq/Vo2w1PBR+bGXwR0Fwf5nIWucr7hd2sqqwg3VkcyA6Pcxpnf6Yqq2iLDWEUeM4xNp6dQ+kdI1+UnWeMyp+ywvJP9fsl5PPCvalCeYBf49+P/o1PpiPLzg5CsxAqm846Dny5mGv5u32Jdg5+hH5eVyce0en24dP6CjaN9+ZrqL3A5/uVrtQiItcQzXNDaafN5IdR2B1ogLu6wGal3BaWfHft/UFXgRNHTtMKfwb9n1hp6SZLQy9Lk1Qz2b6lu2QB4Lgteq1ewdtxizV1pgmJ4+qy7o0VX6rOAQgesgdSvaUPFm4No+fd5t4Lzrp+dBt7amz1a/IunR2Kh5r2qjxmgBHmJwYke0dksisrdtovHXWibdFxnmT+1Kae2+hYE18ovN7DitBmeHXJd1+OSkFTTgPhAU73WXrg85ZDKbVFRaGvhsty888P4qkawInz0jgnmWTKgIQEPmuJFGDmlLlEI6sQOafcARvoi/0aNKFEJ61Cwuhc/r2/w0hPsaGDPvVfHMejo9Tx4XzXyBHlBQ8sNgxehz+fhRujEkUdRjN2+KGXuvWxxvtXu45MW2YNQfNwr22VtLRRh31sF/SNHQztH4s4QQmNxRrAZcnS3yQ927QzpED3KXbRLlJ/CvmSfJUj+ogWdO5SVemwNKwFih1VLY6dS9a8zcOV7jar4dUfvV9oPi3cEV4U3ofoeDQ3ght8cEq+XGBuPs6iGJHx0S9PduI42L2QLSr8Nb2sFzzkWutaBhTH55AvHbsDyef4D3FChTkEHksQcCzJRgdCUh9dCNN4f+bTSV9ZyYWdz+HDz3+eJxmToEf/xo9yXLZWp1Y1HJ/2hRRAbn8DZqULRGY+zk/tGueMxU++YXWD/8JQiHR19H+YMhC1nnd/7TA7sN9moY/FS1pzwGq2LykP7k1+2PcJrjwEK2/DiS7UGc5+MPc6qbnV2KzrifcWOZaXeCZkrNNzZDK3jguobzJ9NVXgVf5fwZJh18gmMA8nxeRkep9MzBbbtKhT46SLRa8Y4cD6agwbmv30hUHifrMXUJ1GqdWhl2CfzxIjOAahmGVlow7WsNOcpxo4vxhW/8TRrbb8OsLzxX7HFFLm/2Tsxp+pHcS4xz2dNhYPyz3zqAALttPWjFSfNBP/pLR+y9RvG9uck9cR1HKKabzTrpzXfFuxRUyIHCynipjbgqsuO1R+uGZvRnw2qY3uts8NoqxbUm+3bTr4eIDhoG4U234mQaA0Fi9Ic3+LFhNiBNFpg3UoQ++YnZTvTeEip9Z63j5VQSpt8vPiY2pMw4ID2to9pOY6BRemYn7BRt0oBEvMb8YxHs2uCgT3xmzRH8e6CVnlwOnVnzp5NZvvX4xjYAS/OmmHK+bk+Juq/UUXQXsz7OavQCf2xPuuvN40EHsHqpKJQxNeAsgf3FhgDEFwVsCKCj8cW6WF8bPPAznlRuVTU71YC9/q1S8WeLDtIOfykMY3qDBCejLbifMUd91tByUa4m052Khir6h2kC3jqYrmFeSVbYeZ22K5W7BS7QIMZ41DxX2GdA7SfqgVHT5ffNv81AHDSpazwMZMjCQTM4qOwt/LX9sotx20JZYSQQcSCpvDy0PFlgroCOZbo9A85JXZ9WPwj5pFTrq6eLqORpSsm/cXvWe5be/IR9IyYI+xY6NJBX1+cpdQ8DqEToZVHvOnsmyuZdy7CH0guSatVLVBJkmK0Cq750BjasGGgKzlcPEiB/hLy+6xI511v8jIK2963F93uYPSuyL9ZFkw9HaTGHMrpZjNHCzPyZIFCcd7eUjHrvpyn6xlOclqjdAh6K7a3p0yHkNjLwbosit30HXVQJpAAb6NZczuR1ywvrCdXgy3poM+sWEKg5kJNECmLmVZuya4FJWZNkyvxbzTHOJNeYKRvh6xsp+ILNkNwdp9111iOwaDySPCR+J2NJKiocu75lP/MJjwWBm/370tqQsZ/1RpTdqLHZisWQiqnkWH2aOP4CPvJ9JXJTzxtBpbtY34aoPbyzv+smSew4autoki3aMtVfeCZ8Y4Z/Sq1fZZB5v29QgvchP7/zyJ4/+x0WAyORe0bAIFb4xuvRYvPpN/X/jgh+H/iSLObZetH32JN/FwXhAxR3V7WEazC71T2fD+C7jgZ4D+FDxYLI2mK80A+FxF/hp+q7cLz0KJzwsArElGwl/5uaniUdboKw9m7QD6mkk6ZHS9cUsNek5g6J0D1JLuo4BsKE/dbjysy6CrDjrJDkesXPNFQ4L3UgKDOV1jmGQvev6hphTxj08mO1S0YqaugDP7fC8n1ON0eNLoyz9zX1tWj2wTlhlaWDyiFjwkZkh/SEqGier30FAZoQpwGX9GPips5rOdnno+B1mnuwNJnWkB/RVqHRQ4hJOqqdO15Ihv1jkDNdpCjytSabavDfiEIgn/pthHmYPHqsaz8xgpHNvOX65CH/TYFSWOZi/6LTNKRxosPxuLKWTCodU/wC0r22YA3IENwRATZndjGWoXf0pxJdp6n332ElOawoBwdsm9dAH4aMl2juTH+Crr3btteQoWWoow4RGWIvIwAzn8iNg2q4zmM37A1DxbSnm752nbZd15WEk2vsWrYEWPnPstxNoC2/EEsMl65/g3cK/Q+So29kg2In6KGgDJHMzXkTcV8KggxnQRDJN0qQyFnXdm9TZPHSLUKz4u5tT6nQ8h+eiS3fC4+e7Y19HdkqxM5JfHsipy4h9QVeh7IUu+woFmJpFwZ1km6jTkMbFny+jkIfGkgN+6eVUEEmVDPdWIzl2pbw5RyFZb4Bj0jfii4Bnl31XA11SUzmxs91SdxDdOerFNa08eFEh6NoWHGNxh84pL7aWXptSbUJV953I3rQre9wQZg0hIxwzcr1XoEimQfxrawQdiW8zrAnQ9qrbWoBlAMlwthSFTBMa+j7v0Kfw/ESbIsmw4IfCP8xt8VnMB3IR8tHZdW+Bp9rZrmq1/NkF4GCXr3dWuOcl6399z6Cx4tyb+GV+obE2c/D0tg/SMxv2rW2vRfx4b75zM4/dgMWdXUkui1chW1fIk8f4BbScRJ3qNLtaIaXlbPbvV7iu3j4Zx40KWVIxF9fLEHVOU/a9Z8f9SHcVCkBYLqzZ983tTzadHuJOck4T2b34CXNl/DobqfGHMmxliG+tRN4+KabRyCfZ95LVGl4xAB74n33uLR3vkWAohULuMv5Usx5/ELqaBC0I9Ng9FIKcAyohKHM+3iH1keH8MxxgY/Z54Vm9DJNcYVpHP78esjAX8j7QP9xtyNHJGcF3s2P5GYq3Bvnx1XwBSCL5DaeOUn5GQTF2rkTTRLQw6OI0zGqjdOZqwoxdrnmcIQEDjKcRXdhtrB2+PFV60yHQQLWE752+QlUyVdA5YR4+cQS4qajUN8OguOndsqytfr7wjSAxCqQylhVqYM4YSJCvbcotcLQdDc08p77kanyEHfqhSClLkuIzses92DQpm7sY3ljjud966KtxqjX+jNdxIf7Quhy/OP4fkrU81e0CjOV9jQzIM6WjjFhMk/uhv47N8PmljsZHkXXpgujlEg/AxWPrQOuhaVAoUmcqTzIjYBxlThfWhw7Asij3fsq1XdQ9GjXT4SnhINYGunzP8aSzvhcycxMcG+YQNCVNEH+EeOnPF9ypaBb174uoMmCQTSv/l15FO5sKTR+LXx7PMwAj2Y6O13nin09FL56BoFpup+rkqe1QsfWJH7WOHiITW3qmKAvdityCRRsktO74qI0QCNvYpewuRFzKaLKnePs/ZObXtfmLL654ukZfcEPJFwAvPFMw6lPY6YUcbnscuZH8b6zNjS5sA+5bygT9yCfH6ttCpC110Dqcb2bPRdJ5ye/Kgcnf9bJnd/K3iszCEnLwNS4Lv3n30r34xZzISt0TYpR0nZz3rjcM1GvF1gLHrchnr2VcZOEek9nfmZHTjGs/87YY+WL6x/LDr3vZ/qmG93XJ5MCKudS9cFn6chr3oQR9J043HqMdYsit6TabDmfnzqWugaDiz+DQ0Pru/1enR+b389Uoc5rWKBY6xje+pKJc+r/NKasJxZHKKW5bix448lPVOc2O4d4idxVqaFJvUWFIb4jhqFTrWKRoywgQ4Jy7kPAl73D39ZAkav23ivRT/fXa3Xe/N/5OpLcYCsnNJVexNk3vvSZtZXu+Z3KG0Q1xc3JPDelKQ+JOksCiF0JqsVgJmvTcOmUR4qPYwQXxNaOFXPx8gzcyjCM4vLafNgwzZwV7+miTZITdGcUVFPoc0e7GLtR5JibrS2oud51DCJaGeXB7mkYr12K4VkkSmOd++rrjtrOQrFRu8fUzo2SPgigc+PJ8by6YA3nQ+nGdUOyuq8mkelv3TCodDTL9etRKPJoGqVUIzL/0fbUeNuQsdGzQLEJ2/I2z2LCboJ/mmnfLYEBJTQjcU//BqUsEWz2q+1s3vh377v0mjIVDtwtR/OLxg35z4x4IJPgvm7fxwDf+JFFiBngOyCzq14Rv6mn+WywMNv6Vq4nyJrcQfcJPSOPX4mQ9tH63fFJG68PXqX22WfzfZxClrytyfMU/GSbxOuYvBwCH3T9Tz/J8l5kMr9GcnjsnovxO4nzf3Bv0HDGqY6IaP46CHXWh436bt66JWotZfiB/Bc8t5eVs6GoOfQ8qo0a6SQec1fwTStdGLPSqEIMWLdh7vHEeAWvqOJx7aa7RbOWjAmpyqKJrh/Jd57KXqUda0szcOdprzjeuxdSEXMOicY6dvw5EiYGjlMt+zTZh/Thj4th86xGuCozTblBAsfHiXPdZXnB7K94vt3XhKHdL1z72OXfotE5ZI0Sc53zQe7P6ybM1W4OHb57Kg71Frc6Y/F/5vh4LqpfZoNht+gy+7CjN6xKxP8lLxrD6ucurUQv+H4LRcZw/y2sgHwgcl4P5nyoMmHH/PHmc63TbLbgj+x3z161/K3Xfv5AuHSWf+0SocP5vCq2Ih+saNU+Af9E15I/WQ5ah5+AR1JAACLP3T7j6blYzROZIcr3Rnd6m+/hpYnzf0e8mGl8SUnqOureSp7ca0QqmHX77jxHUTngdJxWPVeVOZKqw6KesyQ37hcOXfYn9VP/klxMw8ErdhEDtJHOqyH4FKSgn3rnUHyJGsIqy3w/dbGNnA/dpV39oXbQj9VzI+Sfp5oPAzswI/2YvJ/5OEwuwoeDW/391fB/bDC7EvPMvPf+LpRm1pCe/tL/QkOHH4Cv7iPd1vP0+OjcD61j52PeZAcBHB/SadrKP/EhY9/e/tnuifWsDx+iT1cWMj/m314lOn0fa2/uv+/H3+Tf8miG+/YMarqdkgpm5HXLWxhBiw140LqFwWDcekiyQr/zbO/h8uvfba/xL4lXNAFJIov3Dd9O3Ps/z94O2Jdahd+9Y1psYn9xc34DaOLTDdTQ4dSPQ1DiQXojHqnqROIvo3jzwT5JISE5N/cjc5mzB8++LPws9//eXI8hL3v/pHlfs/9qj01f4Kh+Vf3n8XnoH+/CcX/okP48XJcRx5V57uL07c/hf6b/ypTuILH8SJ8eGfeHgyX7wk9foHk5jPixTjoRn4dQX96a6jKUqhgh/TMzXIUuwKe++WDTUakWBdXf+WlZcWmxccnB2dIp4joySkdaU9ewWlJRUKMIuLy6sM7EwsTW2Nbc2tXOCdHR7enl4f3z58TyiTH+bLCYUcGz4Wz0MaImJeamZybnp2ln5AmHGaFVVeNfvaGws7K1tL22v86xwMfi/MGI98GODzMnMz9bPrSOxr7Wx2fDn3zf8Pr3/lUsz8X9D/f71L2/Of5U8cp66jS7R03Rrobn5PQeVj57+a5C2iFeprfpbPyGbmuL/6ePa1//O/tM/6H/8MP0A1nNf+k6zIn0Lhs3Cjftg/nwPp9J/8DO0mJIf7T/1E9OSJSZvIbOfn9IaMonsaK+70XcgyN3nfhknHlCocLFsLX6XpStJozlLhxbj1xPbriCo8/144MseRxNEkbDow/iReXwMW0atHVKmm1GZMutAUa9qbGcfrVQtJQPVft1B8gaSgQqOv4Bkjil1xn8h8m2YRh846GQDOs+cNSJsR44t5Qnht7+vNELxlqXSJRRwhuqzXsblVjFG1Pu0HuPsYJLYG2ZjD2Q+NC9nZwqGP6xXKZoWehy8mVKtziXmH63WFnL7pNhaDkC3r8qgYayrRJ8r8/Z7K37r1GDYUw4OlkJZ7f0a3qo18L3cybQO1bYz18rq2msZ1srPqCIXI6/Ym093IoJwpZuKXdvzOD1tEMk9wqEcrt6SGflL181mhyVRVBY91Wk/PwDMRMC33DBVopkVZwlzYv1RFL7mnbkXOebOHoHB759vXHH41SCCOBWa19VpnZcmtKRB4jttpCRt1lAwQVFYY97s5DfrozsZto8/cB5BBkw22IfmEzp7sDdQlCcohpi7wI3OSppe9C9AgHKC+dkaxzg7YBJpfewy0L64HGQNKu0vNDgEQZYwD8jr0kyHDWfkJIZS9zfO7XuJSOAp9LtKhWBL3tiBDRfRpKr3amGs4T+5wyK7jR3GgKgSN9EWGKWZQxkI+v9Ik18K4xDg3yi29n8NI0HwgUeB83THm6U3Dy4bKO96up/PlAZnnc5DtF25Z3cctgaRF8CEcRx5gRvqfhuyW+nuYvbQ2RGA6QRQe6Nsqry3vdGdx/Zx4HylwGNWlGQhkRu0gtJZcLTKA0nHpeeXK596Mb+vhBSMmgxT3yi1inFfFScgxtZofNhNVnLM+HAKEv2udFoBUyDz4AF3ZR9bmuBpWenkUDmU/1DITvyxIUnkp/0J1yRHo0BSb0gHtHphDFeAJhOdmg7+Ak/pFGdaSalY1F6pYLvXRi9ieRgAW5swdhizcMNcC+/G8D+S6gHkeeximcDjdWTc21UKStFhmLzK6FbPesX40EdEjUL6TNKRuy2Zz1kIgwEn8C8Tm+sEms6XsSYeJolesKt7moPe/ImuBcZGA2bsyrctOI0b/KaKCmSrfBd6TmP+l56tj3exic5vs0ilMMr8rIsN9YBR4A4BQpQ2WVU52j6Nv0e060MDCcLe11vqNnZyUgbPu4wClQ49isXRfHjh+NE+Q1Klcpz3dWwcq99wqP4XXQB13YCBjzUoatjqtNJBcRnN7kobyGKB9mHlKQ1Ls1k88vXJNdabfg17VLDOoTkiZzaeLJ6i7OLOeN4+nEN9tL+9NeTx9Dnp8Ah6gt+4ynhQL4cqzdn/O63i32n8VyfteZfXjQTfVawZQsl7fm9h9LqNfiQBrGmvVBGb2uRCei6wWoVWLNzaYgjkbGOqNObCo9/h4VqCdrPqr6zdXFgGXt6gZy8lfXgZc9R+jIyXzDcw/E2/sniZZxuefvwoXHHi2X8oyrsci64u/0m+pyZyDjrapyGMxL85+kHhnVii8mo42F3oG88WfPL5N3KT5cYTe4eh+javcm9T0ZKnY6R4h7Ivmd8YgZAPvoIIS4D26XjfjoMOMGUIjItdyYceXZef3L/S+XltN5Z0ktZ/ePFqs04rQSZx5zj12bsulvaqZW9fRdX3YFD02RQzAbQQzU+BoulOtimxUr71MK34vrwS0M9iF99gTmOlQpg+RbM7t/VoH1xBdMv/+KmxYQelQcTdC+w5myIYc6Mu8CiKnl/n7uimB60EQIM8s2IC4iwxXsiujQGTz5GA40a6lm4dJUEO43PPb00eNo1FV6r3x8SLuOguNPBs2JCf1s+e53z2eLs7R4NAO1QzNPN++cTcnQnAzx+iA5poKvdXBlkVEbeDkgOhl46BjsgqP1cdipPF2QvwQuL33Hg2+0h4s1fr1LIkk3QRh2/dvmwOdcN6cI0RGCQU5aubYg2g=
*/