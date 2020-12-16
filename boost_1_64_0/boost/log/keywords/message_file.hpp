/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/message_file.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c message_file keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the name of the file with event resources to the Windows Event Log backend constructor
BOOST_PARAMETER_KEYWORD(tag, message_file)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

/* message_file.hpp
x5ufktgoxZtJzHXFmY//pvLOrSgszlDdSImgG3b9pGn9SFvVen+/l8/zHdpWd2i9T1kbWu+mukPr27TVKyTMdutzclV2rXPiDatzc/2rFLdl1ixa6jzE7b1nS3iz+JtGuH6m3u6VY82l3jZRXlt66TsNb0cp44GRylj97+2l7zRScsLK2L9fkhX9OhimvENszsZ/1uf5Vi3vWiST8m5xo6O89R1WYbH/JVbk941pEm6zvGssci9zjdsjz96nyecejAqmiv7N5ZVio+TeCSh2huv7RPM+Z4FcbwI2319qaTP6vsl5X+G8VhzS8uiv5dFPy+OIKQ95/xooFNd3eXqtkDC9rZ6RrhNaDoF81tu/TogmDyd6mzXNZeul7yoz15k8yCBSMlJYWSpfjUPvL8yzfLaEaaffYzUOYmauuTMvHHdZk0TDDBe35kFtTNqJcUs27WaC7MdF/V3aeR/QLOh9baVcX4auM9eXoOeS3TnhtocTqeeidU5by6P5jlO6oHQ+n5FGLyovnV9S5bQRnZBbp/1h4jpzG9HErfaEg9O9s094upPwW1FfusVWdHTprlgXva3oinVnbis6Ibd+W9H+fir/4vB8b7YNtpp8hw+HoKokDzfXYxt7zVnUE3FrHoLvX0b0DU9vZ/JbW0d6K2qqFvl1q3vdaSae0GfeiupK9zoyfs33sQbkr7vJX+jzF+cLyXO/fuF53kr4XXXkWdUyqnra1QC93HUWenlzFDbM/e3xhEueU6nnvSF5Xl5OY+Ruxc60r0mKekpeWtXTHveehX62CulHJmi63+gfnu50/B6sP91aZdGl/WAD6uzgWdRZqyj6kvdhzhnYXm+orZFPyib7SbFxkvTAK1+8+zsbV+2YWDpif1r7FZFtmXxxoX382LribV9v896+N9Lm/e7Q+id7NtymyMdtk93dZsm5s9V+W674n3JP3hvfWNKvtteRw2//c2uPSDbc//tssrvb3D93NmY+DMwNk2eYvfjL4vcT5reMwTC/U/R3V343dfxuzO8jnHs0vxMdv1P5fRR2Qmbr7wOEOQVXmnmIMs9R3GQOiaanVG0ML4GJtleYAsthGqyAbWElzIE1sK/aNu8HV8DBcCWcDK+Fl4t7wCZxhZ7/Sj2/0ybxHzCbYfM1mAYpW4n/XdgfvgcHwBMwT/cvhX+Gk+Hr8BRcZOa1cT49TxJSoOf5UM/zV9gK/g22hx/BbPhveBGM81prhsImcBhsBOfAxvAqPW7ypXPfMl3yhbucby5MgvNgC7gAtoTzYToshh30eEdYAjvr/imNd5eeZ4fuZyAv6HkGar4GwSZwsOZnCOwOp8IecBjsCYdruV4CB8MRcBQcqeU6Ck6Co+E0OAbOgXlwHrwULoLjYBmcAJfDifBzMB/eCKfAm/T8m+AkuE2P367Htd50fg4651JvD3p85fcQbA2/BT8L98K+cD8cCL8DB8N9cBT8LpwFH4WL1d8pOMXMS6FM9HyNkTF6vmb4s9kcNoEtoIy/hBfANNgTpsKhuk+8BNJ5FXCmxtsUqdZ4/6L6cAI2gW/BbPgO7A7/AXvA9+HF8AM4EH4IL4F/hWPgaZgP/wanwr/DGRpe86fzBKhLl/x5NH9ezV+85i8BdofJsAdMgiN1X+tJx72jQy71dIXq4UzVwytVD2epHhapHhaoHl4F+8CrYS4shMPU3yntK4r0fAP1fIlIvp4vQ/PRVvPRTvPRXvPRWfPREfaBneAAPX4K5pgx3JSPxu9FsjX+OVpfBTABXgWlHAhwUMOd9PjC9bT96Vzyl4jfC38OG8OXYZLu94VH4RD4KzgWHoPz4F9gGXwTVsHXofTd2n48sBbGw3thI/ggTIY=
*/