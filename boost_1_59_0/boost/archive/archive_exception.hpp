#ifndef BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP
#define BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive/archive_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <exception>
#include <boost/assert.hpp>
#include <string>

#include <boost/config.hpp>
#include <boost/archive/detail/decl.hpp>

// note: the only reason this is in here is that windows header
// includes #define exception_code _exception_code (arrrgghhhh!).
// the most expedient way to address this is be sure that this
// header is always included whenever this header file is included.
#if defined(BOOST_WINDOWS)
#include <excpt.h>
#endif

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by archives
//
class BOOST_SYMBOL_VISIBLE archive_exception :
    public virtual std::exception
{
private:
    char m_buffer[128];
protected:
    BOOST_ARCHIVE_DECL unsigned int
    append(unsigned int l, const char * a);
    BOOST_ARCHIVE_DECL
    archive_exception() BOOST_NOEXCEPT;
public:
    typedef enum {
        no_exception,       // initialized without code
        other_exception,    // any exception not listed below
        unregistered_class, // attempt to serialize a pointer of
                            // an unregistered class
        invalid_signature,  // first line of archive does not contain
                            // expected string
        unsupported_version,// archive created with library version
                            // subsequent to this one
        pointer_conflict,   // an attempt has been made to directly
                            // serialize an object which has
                            // already been serialized through a pointer.
                            // Were this permitted, the archive load would result
                            // in the creation of an extra copy of the object.
        incompatible_native_format, // attempt to read native binary format
                            // on incompatible platform
        array_size_too_short,// array being loaded doesn't fit in array allocated
        input_stream_error, // error on input stream
        invalid_class_name, // class name greater than the maximum permitted.
                            // most likely a corrupted archive or an attempt
                            // to insert virus via buffer overrun method.
        unregistered_cast,   // base - derived relationship not registered with
                            // void_cast_register
        unsupported_class_version, // type saved with a version # greater than the
                            // one used by the program.  This indicates that the program
                            // needs to be rebuilt.
        multiple_code_instantiation, // code for implementing serialization for some
                            // type has been instantiated in more than one module.
        output_stream_error // error on input stream
    } exception_code;
    exception_code code;

    BOOST_ARCHIVE_DECL archive_exception(
        exception_code c,
        const char * e1 = NULL,
        const char * e2 = NULL
    ) BOOST_NOEXCEPT;
    BOOST_ARCHIVE_DECL archive_exception(archive_exception const &) BOOST_NOEXCEPT;
    BOOST_ARCHIVE_DECL ~archive_exception() BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE;
    BOOST_ARCHIVE_DECL const char * what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE;
};

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP

/* archive_exception.hpp
/AlOaJPlEyxh94vNIL3bWiTubJDyyo/R9/c/q8fTzmYWLrRSvrxKHFsw6GwZRLatCWB5nk6PpfefSwY7zNqJMLS9VgoxSFYD/0+PvMS4PFEXS2wh07+G50jx7dPryrkssKTDEufjyGirEDsJmhzvCoLRRtJpsXS+lN5JEnyKaYJZ9aQquFQHTR98Owt8iZXc6mlKuOjqw3WfjGzQG3Myqu41VjbdErWUSzMICtE5Uy4pV7gsRl+YEHHx7WdQ0YqVbbnX4ueZefVqIrf3S9u5O9nPp6MFA4Oa+JvLFyiUVGW8NDbDISPm22pyWAL1BVCo+NDlscNclwIyxv/lR8saNlZ69KgnM0h0HdVVZ8njoNnXR5ntHVicYyHnislGS2grJdV67uUdAozJb0cihtKdfJQSpDevVrovwNIY+sUZwluQ0bDbkAHb0NrQyes76lO396b36ZhTuvXrg7HFw2s7SfHuI9JvvXqEU4PVMaCR55Z2/RTPVw2y9d/P03xthY6mrppkCw28n61gFH/xWewhT94eYx9n91dC1kb0vHD3yer0f5FzYTE9MByfrP5UjNqDiRUbl01RxeEbchHpsYuXoziF7me6o3EMp96wDE6l6heajkO3ZLlHPMEbqZcF1axYv/+541ycl9JWKLfafOApYfsMFdjoxrIjuKfO0qF66b89hztfTEQeGoQSp4aerZF237Rbf1uVetlL8zr2903Tf8QxdVUV18t85QxkAgcWLq8kTsvRIjqDP0CmyBRBkuH205gEYc/Klb96qaulVVT3SE6mWeEM1TdPzmXDMSaiXAqu6tbfoBWdHH4ch93YjbA0nvwzov5KTDdVT7yC+9XkTFv26rIbRUv/DfluZ1uuki336ZT65QWrxEs6e5+rmsV+4rOwcGaA98Y5sl2IeXb8Lw3myu2Eqwb8mOeLmxR7bjTiEefb2pg2F9Q46WEW9BHEZqIDExWlBL6tIn5keGav/f6twIYcGVLKj5Z28gb+U9VnWoX3q5yO5ul4CEy09r9iExA9ubENvq4nQWxS4Qgu8gT65FQenXC4hJFJuvIgaHHz/FrlAj+jJroscvhYiSOPeYhkej9AH+MgmAuiOCfaJVIwii4iRLa8lkG4LTsiYT8DKbgT1QBYZflST3moeREHRrfOMXLcwqRQwUiIkuOZgfzE887R4bFj2XBB+H1R3m2kKQM5UDgNrsp5VZLA1y6uuWAF5UGch7og6rxDHcD4Knkfnq9s2aQR9hw9Qbg8jGgrCGadqIFdEHUyRln9iHQicEyq6/se7kmhDOC4dC6YEtsJg0JFQMT1uObStLFlempi9sDu1y9uuc3EdYrHFWXt842mwZXlWXN1X4qLYqcomyt5T7sW0hpLOVR4qSol1XIFRmIScrJw9Aoqkt31vB/bPlZ65ekQU+EOPxXBz84yDLJhnyZ32TONJdoqxfmoHEZl3yaP2FuNNdqtYH3orM5Rn+nb1PXyvcQngJG1xHYf2EkO4ys04xZ4tfj2XxNUItoZq5wh8JVdx56RZ+J1CZgNSDMKr5QhyQJAy6t1XUNI8n/AHgmtfUyeGL1Nh+TpSCLNChEEMaeRYxpx/hFcMVCV6l/DFr+Hm34Ra9jqqo58w3yi8ctAnNRf4xAUoF2MwrKiF4zq8ewxKCuM7zHsFygnjO2ZFVNZ7sGoOuN2OuuAOud+7PcoMvW3r8W0MWP3cOaE6pcpVfpkCXYIOuJsT9l2GDrnAE/VdhIC4uRJSmyE+U6oGsfBCbVjXJyuRoe0VCg6eUrsgnhZNToaOwilOuOORRZFNrydCw/WFWzdxCYVWz4r42Ij6/EUuvt2NegUR8FUKep5dNriDIHQyS++u8nGJNPqOeycMMW/icPyVUDEDwSXEvSJlbVqGfYhHrsfn4UuxI5KEFMnAuu2z1/kHQ+sxU+mQnkTP0S/hVTaSbxTPPzy3WEBCRcUWbFGNtT7toE8Y7kY3+JllUVsDS8GYBOO1OPBCIO7/xWHTSKroAm620DvJ/GDbCecGGc1psutaGqzucv5tCptXq1XY2SxkbVqmlR+GaRc/Ap0+jv00bMu4Zh02DjvGdG69ytwG580Psv5axqyLYcIyB4jIv2inBOj42MqzDMi+lTClrqNi4p1pwRPTWw5hIuTCuzsuUXF31RozJXG+BgcvOsUW1BPGfrdbEnuFHW8Bc7KTPOZ0sfM5ngz/f7OALPXaZXzY7cWMRyhmcKZKdXus5//Lh5pEDosnO4ajaicpULDZKWJ6GMmm2Tm1cKzofuxnqOJUaEgMHsZNccbYsbQTw0282nnH88ONCep7x/MRrbqqb2P5SLamncTjOnG8Y4swV0L4CHUmqiuTzVmXQcMW5Q3DlSysrRcDePymDfeCmRxvpunK8B+Wa4PhbZtxNSSGObPzwprEbH6+rX1Ow7fMs2BthOGb4cU0buA2FVcC67Ej9ogdwoASDBeT5oZac9zOz/0X4/RYZc3ooppaMa4wn/4OmD1eUhjT2KWLvFkYYdjLi6hLE/u03iNAC+pvE1DTBYzgzS3kE7+5NHV6/+UxCOTyLHMKRT6uwufLsEn0bDI6XFuu7UFeFO4ysLFbS/bmmjutjUJ7AvUszSbH66stRA4WHjIdq+0mssu+vUW2FlAS3A3Ulit2fXrYqK2Ultl6eCzK7eTeky884K+ywLzBdN2u0EzUWKUvryuERT2t3BHa1Iy/dJ2haklYtt87xp6Oefsv6SeZTstet73rGTCA30m9uRk7m68WHhnsxJuvsx6AUOEDAk59tpAOjNI3X5+5yI+ZCOhKgKmgmQTLYaa1OAwwbKKva3e3tnu6EjxaLvw+q5JebEJIWIPvnjmuhkLe4d9kJH/AP/yncgrcsH8xu3Ly3OR3Pd9zPNx4d/XPWAwxvXYyRmyIv/zHgE3obhSdf8iwMl1n/b+zreb+GHoZLT1KF2HrbbzW44ts/PyMM1ndDjXUOOy/5j7GXmEJ04TJKi3y3DMPPr4ZPS+O80Be6Sf2Z7CbO+bPflOX62K3frtkI16N/reLb5MHO00fdL790jeiu2PaQipiBuR81XN8y0Jn+ZAJy57s9I3/DO4jAjFHEdGVP7T9y5/so5wz0Jkbe63lTzhpbHncCSPg99mrNirW1c9/3u5Na8nbZVn5/txARfyTRWKBzZ+c866W9urESD/n4KVtPV1u3Zzv1CONPySprdmKFPqG12w6eXNUmT2wGQ031e1ffj3QKU52ngjRMAZM6lRnqnvJcUZe17nXTPqb8K/knur2L4UNOj12/aNgHkuSzwxon/3tmg5vBZdydQC+F/Sny1BKI3lZ9e1BFO8KLbjRfKRkYlqbuBj9csEFEXuEZumRdhqGmBRdf7weObxkq0lrOHiVzq3XAQIRZcJad1gQfXShBdFIBGcJkYxajbgNZ90bfMQreJyRcy7BhoL87sIv5YC3lWjU61EavC8zLw+fV9aVneE/wMogNd/vJ5Xk5QRBz3E8SeXKilH3Dt5rNKI2X5SyxoudVLOvE+q75iwUiPmIsD90H6y/uz+D8WyWZ9UCZW/c1v+4ZLJYknDbo5Ykf7OpfDzw6+I9n5D6VZNhnks735Ry+7/QP8lNEgK6gtqCJr/lvytafDRhNGE7f8AUClUlKFeAIBDS+29BVgcS9MovFggQHAN7hZkWVyDLe7u7u4uSXB3gkNwDwTXBLdAcIKGBUJwSXBI/iU5fs77nnPvd+/3vc/z36Gmq6uqu6enurqnpmZm0aPUY9Sj1WN5hIWHIhtc1I3bzb4ms8a4ZrP2cE3n7hfE1u6tgY1bnJKcXjlFOVU4ZTq1OYW9FG1W1WJYolliXqJaYlqiW2IVIK/EIsXRQLENDgsOC5EMlgzxMa56qaDFaodBis2FHIeSGfy2G2/t/pr0GsOatXHFUfRR5VHWUfvR06MXR4lHdUeRR+VHGUetR6Ev5edZ2hnaadqZ26namdrp9jBW8IUwhHCEsITwPJDbghWDl7tJjWuOyo7Sj1qOQo6KjlKOGo5ijqqOsl8qXhjMs96QE2ME4ARgBeAFYKIhdyF33e9CCUQKRA68Hxbc0425VhqPESElQeuijCGhjGWujKmujO0+gQHqvWciBlS1o+bCywyX77Mwca0NmVexo2nEWwy37/Mw8QXKfgl/b4IIlNyj/xjpbUJX+2peYo/RA7stSrA3x4QVaPglsvgT9q3JY9RICuAjcO+KCVltjVfkvOIeK164cq3SIyxTk1oCfMRwuD4RiJFzOI8aMS0avmQ4VZ8yxMo5mkeDmC4WXxGXLhy7TxpiDTE7djtGPb77qIZSAffuS5t0Hv0sijGckT5tiF2taBaVRqQ6RO/4Ua1OJaZtH59zDo+hgK6ApB55DlMOXQ6rAbkBPQsOKxYrHismKy4rNis+fkRUHw1E5RjZOd2ryCvFq8ErxqvKK9urw+uZV0GzXrt0u3a7RLt6u3y7fruYHsUKQzXOIdYh3iHmIe4h9iE+GYZmBHpkRR8nRAzSA6GCFJh0NGvo0VXjc4fHRRD1DfTJQyzufqjoovAi+aK+Wd0P7Kfhp+Bn4Hf3JZC0n7afhJ+6n7yfvp/YEq0D/irOKtYq3irmKu4qtmf4YRRZOFkkWQRZFH+fPoQO4uAc16x5o3Yjd6N3I3qjciNzo3MDvtG4UViiC2A9wA/EQA8XjhSOEI7qCkfsM+xb7V3tE+4V7uvqFYMYH4d7qclJib/ASmqmlnpBLV1XKFVeKN1qJkWoAleWn8zAmfhQVr6wWAVU1jItasPQkKgja1/YqMJf1pEMdVHtyp4lU7knuxQJlCVNa+9Quqe0Si8XkaoolqUls3rTqJ5IBzCQIxTF46RSqjiWxU1r8kns0J2mIReWqtHjSgP/8Wdq2xzWdW6tbqFuxRwSjAnFMlOFKmVyGSxv4y1kNicfWTeqUbxNYCxitK52S1VjnpFqUMnmUMxgzWbOpmKOH0sZSxpLY4lnScaTwZfGl02TSpNJk06TjSrsm8SyLnMLqZdrVWmVadVpBbdqtCq0GrSKtCrrsCxTLz9apgAFLPrTXGZcpl1mWaaoij9I1pDxlPaUPZc6lzmXPpdFl/pXnzkXDhTGTK5P0lq/qpfwEfVR8ZHx0VlgFKQSZBKkE2TtIO+g76DueNRB2cHYQdvB0kFhn9Qo6yjjKO0oeyh1KHMozV94XoReiF4UVxhXlD3Jso1t3VQvucDkz+hP68/iT+HP4E/jz+xP5c/kT7ef1Jl2JisshVhIVpRbmFtkWPhssmbScfJwkmwyd9JwkmL7pZs4HyONGaVq+pAenplyqpm2hpn6rJk+1wZqy5MlpbFkoqGYTVoX1Zb0JT2o356sO1S1yeWi25K9ZDCWKOjSuCQylsA/3OKSsyR98MgzoW14eePABb2lZEl2LK2jjuHarIs4/pmLFNoIZkvTkuQBUy7ledL1CIKLGkty1MZzvUcDmzAnj73jBbRIKdFTwoZ6NjFPpLyTBXRIqeJSBobWN1U375+Ieyf6ZQhoC+kLiQmp5lCmDapuWruU6dEqplkOgjZdvFMFdKvjtwZTXFIENIVkq1NtN3RaFHLoxtPGU8cT8Ae3hreGtkbwB/GHUTajNqI2ZTdkN0c2RjYlTky8I9rVOkUNaA0ZDGkMmQ2pDJkM6QxZV8lX6VnTHBMdUx0THFMckxzTDn//WfXm776l/v7zi+E3pXqsNSlzQ7ubD05MT8CXzt5J7dorlMIUwgzCNMLMjim5CbkpuUm5aYbxhsmGiYaphgmGKYZJhmmr8U1Di5vcm00bTZueG56b5xskJ9cniCdhJ5InAycK3mk3Ee26K1SHKcIpwknCaV3xXcldiV2pXQldKV1J50OrI9ebZBtwJ3EniifjJ6wnIpeal9yXnpfol4qXrJfxflpClGQp2MjKpd041UiRpVKRlfSR5VaR1QQyoZOPrUvNGGOS+2Wwi8om5ayr65V0GKuSZ2WIiqomFaxrzBhIaXS38zboSVL0aBS3C900Wun1UxxkPIvCJlW3izaYDPrU/CIN79OL0BQGp4RP6m4XfFFXUL5iuE2BpSnHYZSQkWPQgAwDzPPYpQgrUZVDGXuS14aRzAvZZQiropX7GdeTj4fLhuHNX7BL88qnV2ZVZ+VnlckpyySXDXMUqTGoFjOBktNlWthl06vU6F2TZYpk0iuyitSYOGWqVEpGVT8yWTJt0aMku6Z8Tv6cgpKMkhIyLDHcN0wzXDRsPrw5TGleWyeuXa6X/0i1Wq1apVqjWrlavVq1WtNByUEtlYmbgZupib6JsYmhicmTnimZPyVlWH94eVhwuGPYf/h2GG6YcVPEvKEO7C3lreUt7q1WpjnLuJt8OnxvE2hecNJcJ/2+0k45RylHLUclR6ORcZx+nHGcYZyJlZ6VkZWBlamGvoaxhqGGyZF+MXl/OHNYd3hxmH+4bdh3GG3TfxNuU2yTatPUvKRO9lL8fdWe8hljLmMuQy6TIb0hI9QemVbpVxlXGa6TD1Nuh9GHYTYlN+k2LTfxN/NOKk4yT9qg9lFykuYixVtJrBzLeD+lVM38D194c4rZ53GpgWbANqYNEQtq9sVcmrqlzDMaNrYNMQsa9iWNmq/U4jKqPJRcp2P/8D33gth+2ZnKZ/Uam3KhmZp703kPVXpsxPerzpSvy0tKb6e/2jx5qI4yQ8lZjFfh7B7Ep0RSiKYRVio2Y7zj5B7Mp0JSFKsxUGo647zjdarm/vTvvtjOLhrTYJrmtSnSKRpTH1epmHnYoFGlulX2eebVjOs0wk7LjvfO5Q7CTsiO6Cnlqckp1qnKKfupi3tCq5b+Cxb1GqW0Ms1yzTLNirnSufK5srkK7lLu8pGZzOnMGd1p3ZnF6cUZ/mncnewdmVOWU4dT0lODU6HTgFMY95SrvFYd/QKhQqFKoRdC5bMVtjPuOz7uz66etyr76y0XOmg0lSqWKpYrlilW6M5YTlvObE1vzeBP48+kTafNaE5rzsxNz81wT9vveJzKnzKf2p+SnOqfCrqHXXVePbnKv0q4qm1VXS4KeHGgcV7qO6M4Mz49PsM6zTpTM10z4zjtOHM47b9zvhNwingadFVwlXT16irKR+lW/Vb+Vv9W7Fb1VlawkFQjrlRyJhjMUQ6MsX1Ka5NIaxtZbJNRbBuams/57qFNug5VVe2suG0551SGLXN9KvQq0zALtq1omFqw1c6QHJnls+LVkWTWHJnis85uYNHRrMqc1d/NP532sb7M0ARx5n6cg9VRQrE2Zn5xOntl5d+gWh+gE1j1OMomRCcBbyqyoZnrMVHpg8l7tmL1+Qts9s1cokRlMZNgW9P62gUe+3aPci6RzFL5SYUpWtsSW0srSxvVeiz7ci55ppnh+u0FVPtijeq3kxa2uAvEVSoVkx9tLK1ndGI0KmasP9dfLrxf4F2A3dfbF9j324fdF7XP90jwqPWI8CjzSPdoaZTSrWSeSLXRtBqpZ2qoqK9osK23bdit320gqidq2FyQX3i7wLxQtWC/sL9AsoC8r2Bf5JHm0eQR51HjkevRdRbUKOOrpFtVNUE6STpLOkE6s9PQsMBn39Eo4iu3WCpYbT/JZatbT1dP11BSX9JQtQBaeLXguvB5AWUhakF2YWSBaaFiwXZhd4Fo
*/