/*
@file
Defines `boost::hana::experimental::type_name`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP
#define BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/string.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace experimental {
    namespace detail {
        struct cstring {
            char const* ptr;
            std::size_t length;
        };

        // Note: We substract the null terminator from the string sizes below.
        template <typename T>
        constexpr cstring type_name_impl2() {

        #if defined(__clang__)
            constexpr char const* pretty_function = __PRETTY_FUNCTION__;
            constexpr std::size_t total_size = sizeof(__PRETTY_FUNCTION__) - 1;
            constexpr std::size_t prefix_size = sizeof("boost::hana::experimental::detail::cstring boost::hana::experimental::detail::type_name_impl2() [T = ") - 1;
            constexpr std::size_t suffix_size = sizeof("]") - 1;
        #else
            #error "No support for this compiler."
        #endif

            return {pretty_function + prefix_size, total_size - prefix_size - suffix_size};
        }

        template <typename T, std::size_t ...i>
        auto type_name_impl1(std::index_sequence<i...>) {
            constexpr auto name = detail::type_name_impl2<T>();
            return hana::string<*(name.ptr + i)...>{};
        }
    } // end namespace detail

    //! @ingroup group-experimental
    //! Returns a `hana::string` representing the name of the given type, at
    //! compile-time.
    //!
    //! This only works on Clang (and apparently MSVC, but Hana does not work
    //! there as of writing this). Original idea taken from
    //! https://github.com/Manu343726/ctti.
    template <typename T>
    auto type_name() {
        constexpr auto name = detail::type_name_impl2<T>();
        return detail::type_name_impl1<T>(std::make_index_sequence<name.length>{});
    }
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP

/* type_name.hpp
u9/GXv19XTwM3917oSfNuAZtpfrEIsinw6AHHRXHvupC8CDwkF+A5y8vwz4E9RWC/hZhfPdDF5j3MOQ71nD/T8E3IMdKQUMH3IJxX6OLF6aChh+ELQvtrZqC9YW+j8X6LcrFPhu8vQS0p2Mv3zeKyI1ZoLcemMthmPcYePB68BP0//y5WA87Q/bMxF4HOHgI4508Cu3uAP5wHPj3XthX9MEa2gd+8pCv74K//ITxHNJTExHI6jmzwTfA83r8Cn7d2wceAJ4DfpkBGrsJdD4GvGtf7CXuHA5bzoGamL8LZPAi7EuGgAdD9zvlIuiFKZANa2HHiYHPL8Se4QmsV9iALobeuvNx2MPPBo/oAG+rAj1Bj+9xBPr1IrxwFmJtzIUeNw1jfA7rG3vtGOjsNtjDVtwGXhCDHJ0FPRV67FfgSaedDDwC31NPwbpdj70S9orBEZjTfojLcxZ0825YO+DHt6JPGx4F+WA8owD/qRx7qWOwbrIhDyDD28BrZ2FPMzMf+506rBPo0QXAS/mzsIlg/qaXI9YG1mLoWA12KrSfiX6gzofPgR/bV6CDauhNoOe1aOs97O++BH1tPxsy9FvY1Rqwd7sJdiTI4YeHYK1AZueng9++Ydr8mm+CHDkK+ZdjzwEdcBlo5lPwlkbQY99vsO8HvOVF8DfwmXTs4Zsxn7sM1MW+0EF7ZmKf+BlsRfdjvWwHv0/sLRpuwJ7hPcRfw1r/rh5+4LAtLL0fNPkS9BvYMUO12N+Cd7yMPVn8adgT0Me1kJH6qZAxu4NnLsF+CDzpIODyMMjaFzCvR78Mui4CzkqhI6KOZz8AT9DQNuwUYczNRz7gfkfQXDV0VtgF7nwG/BF7+w17gQZ6Yl8PmXn/fsiDbiigl+5+E/C1DroV+MoU6Nd7QW5+Bn1qHOxav0POr5uO9Qq+IJ2VXn4dYxqI+QZPrdkJ9DUC7pCnYr4gN987C3vGK2CLaoU9ZQ7WAuprOAj7HthlKgdgvXeHDtMgxIxW0Alslim/Yt5i4Lewq2UvwZ78GvTjB6yjdvQDsnYmeMlipO+6F/obdPJzgfMdR8PecAzei3hEg93FJ65MB11gf9F7Kfo0DboY+NtNd6COFZB9QcinUvifQeYfdg/qhpz5GfrcadCTtvsMdtl+mPtLwecgl48fC7l0PfYX4PMT7gdvx7z/2Af8uhL2yeVoKxf8cxho93TQ/8ewPzwD+Yp2t62Bbxv22x8BZ9/+Cl5dBh4LPWQU2s8H7+zWGz/bIz0VPGwVcAa6XnoC1vK/WTsTuKirLY7/GRRJLQEV1LJwKzVFQMUlN5ZhUTYZUCxsBGaAUWDGGRAoNU1Ts00t233P0jKzMq3MpSzLLMvKTG3XtMzUNlutXN73/v93Zi4T1dve54Fx7/3f5dxzfud3zr0zf+Q8uph8Jf9aQtBldO9ON3YPd0yJACOHgIPI4Uk78UIVuRMTOYIx5E1szLkKvHlO05rdDTYeJT7bQK6+DTqIbbyHnsVWwpsdcOo78CET4a/IYW48/G4WZTngE3mZGPZqQzfGHcX3IzCnoEX4xOfQm7NgDLprOwxG/YBODMZf3cW84VDPYAfzwIcpDmz9XnJLXeA3cFSomFYP/3HMA8fAjvAxBr+aHmPS2rcL0i6cxRhTwKv24OtueCjkpMBJDhkfH5xu0i6+nbxMX2QLhnT6Edm+iD86REw3hjjxE7A2GU7kYr5bweEriAWY62nmfN1scumXsLd9Nc09nbhzPjLqgf8njihhT64iv1KTgH96Cnmnk/cFTwvG4yOJwyfBt39cBx6xF7/+wv7Cz37JRpbYRy0yztwEz8COnz+Avgw1zgDWwy1vcKND8KiDHeA=
*/