/*!
@file
Forward declares `boost::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MEMBERS_HPP
#define BOOST_HANA_FWD_MEMBERS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Sequence` containing the members of a `Struct`.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` object, `members` returns a `Sequence` containing
    //! all the members of the `Struct`, in the same order as their respective
    //! accessor appears in the `accessors` sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/members.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto members = [](auto&& object) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct members_impl : members_impl<S, when<true>> { };

    struct members_t {
        template <typename Object>
        constexpr auto operator()(Object&& object) const;
    };

    constexpr members_t members{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MEMBERS_HPP

/* members.hpp
RA0KP+lMRR9cHg9YgzXbibRhJ/f6HzRXLOErqy8ftirmw0Qnp0gPUewFQAd164no2XNMz6wVlIlswfp1elbc8cbARtCzFoOexRM9K2R6Vsj0rJDpWSHTs0LQM1qF1GHJSmGyTtXY+sP+Hx9N1RgNihiJPOBGUiRVu/M+pmozolTtApnkf46qnf7fqhm8TtzfnR5WED2sBL/z59RFLBD9SyoprRhcTxKd4IirHzWoYgdRxRVMFc+aZlDFd5gq0n5FRG7sThWD846hihUYnPoHKHhGlCo23X8MVeSE5VpCJMsL2L0idkaUKkZTDZGpiOvZC0W6jmdJ0wTn871Z25X9UH0CHYZDzKmv/jRgB3uTCcpHp2K/imdl3GLMHCjK5j9LCzsdT/bdqMYzNUw2N5O6Le8YsgmnmpT4xDXdeZ42yfFk48f8smQ88uRPvsIpJJ0rpH1DemPt68SE5OKHWZmN+EE6jlTXEJ/ix+aBiYLE5jzCZmA6Vb2FcVo2YzPsPiVia8KeRkOOX+40UYs+NLeDrGG7Q+Xf5qRC0RpsX9KopjC+8JxHP7v4GXSLU7FuMUpybyT6yDTqJSoPFaA8UDoqb5yL8qzFF8K56S+TpFW+5+KHu8ypVDwRDSPSiXI06pkF6rm29m2UlFS7Bbnxxcwa/6TInzyFI9U2wCJ9D3V+DpOyT+gLkkP5k8o/qI0jtdFIodFYQ8NAa1K2HIM0+mlTKFLnRilzejMV3cgDKvnJXIUj9JUsl8oZx7nX4MsYWYXDuCSMI49OYQaV0EBfzUyb8cSjiogo6T0P+7nQdkvAHly08kNJfSf/Vqe+OdXQ8xm1ajsiakPm0DtIJknww7/9fBJsr9guSbDHIMETO95AnigVZpSwtWLtsgwJLgQtllhBvAARW4oVS5ZHTah0w643Vkjs8gPBmdj2JjXSJan1SBalt0/KVF/T2xPT32LWf/thd/pbRPR3Ku83p9J+c6qkvEx1X/ylQXWr6bb2Y0x1f1pmUN0bTUR1ixAslDKD6pLrjDnHUN0iDNGZfD+imKjuYVBdP9pyDNXlhO33yYRINjSQ4BdLpkepbjRVo5ZKvUp9S21Lf/vZBCKdFtuRRHevJLq7AwkgunlEdFM88J2MlBNYVyBq70idvAS2F0I7e4a2n2NrUHEcv8Q1rHa/c977gQRkSwqFe3rAri9JqUldGqGui7shcQgkVGR+xJM/Ayd9NoRg/hcTb4kTkY6NA5sHbniGGmZbn75FtQwOzga7fLC2HY3zw7wTxYgffv/oec/9e3e57J+XQQxwnS2PZSqik361TPKfMen5fp8mu6uebDjXXmVyxcDwiiaUmNotot9ZHCF3M4XdIh5M5Ai5oF/WLWINR2hz7iwZ4X4J7nl+gAhHPlbFspOHBSaAHb5M+9C9fTa9gLss9rggjK8UydmDso5OL68kuCPI15/yuHDUvUftYv21ozLTZY+c/fN7pq+Dy9bc5/b87nOuA+j2j7NVK6ZHZR/6IkMSHj7Rz7PSD98lbVSLrGR0NTLTQmH82aBbbG/8PH2VccsORKQiELqha7/WHHb1gP0ia/C22PYH+X28Ge9nPG+mUzmVQ+6JRUj88xa8hOfVHL5Qvvag11tqDjeY+DWOXstqDi+Tr/H0Oq7mcJl8tdJrXs3hDPkq7fnVHO6K4Vc7vQ6oOdwqXx30mlhzmM4En++Lr1Vn4ssxRtQejp1/Pvw4dfZyOQOzK4LSorNrsWHBnQ+7q84YAjlrpSVQFd7sDVRz6ooY9FaYlssVzU4CXro44TUh9IHJCO2k+xT5ePWLfriSg4P4SUd4IL4YUaT2S0qUYTr4TKMTRt2/Cs51+ZLZxioeFJCDIWw=
*/