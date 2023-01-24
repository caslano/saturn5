/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_DO_NOT_COPY_ELEMENTS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_DO_NOT_COPY_ELEMENTS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Used to mark a special ctor variant that copies the internal objects of
 * a container but not its elements.
 */

struct do_not_copy_elements_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* do_not_copy_elements_tag.hpp
Sd2ldAUuTO2Ovv4HqBheFd3/xYtR921g7WkfF1PbQM76aRjci9pZfH8UnXv8HeKKzuZfrNu3A5mcBCpHBzfHyAGFQTSNDd1bdUP3y2uZD85m94mEJh7y7DCxcaCw7QzSfSjeHUi+8V8N4juvDgzykdfzYKG+N+NGfeGl6/HkRgGwrSPMebAkMttGrN5rE/UpKTcWLI4kC5vx2qOepyJ/ghQYESVSqAItxTQpIAs9hB5ulDCzNAcHpRrXV/5wPUXqQyOCosAl86hsZhMdjEphOTuZZ7FHyaR4djKH74ev5M9/L5U+f+9Azd+I46wKxkVZsc7g1Cjf9dh3X/iUs1/ZLJWpUURD/dbTanSvJZEWpQPsvNZJgrI8XM4MJQGYDLNDc+xWIKLTXuwiXnQhfw2Xyp/B7wN+mNoNznZ/hcOVGgu9b34Fep8HnAuTPUevy7Kw37ZFe4VkvINp0+ypMYjZg6kLhN7XTSNmdlMuhYKHo7SKiEH52KYkmLMF/NEoH1ttRpMkZ4GhUcoCyv+Qf5ueyGxbRmvC8+s+0sLzmedWKRmpYt0Z4yW+58kv9e9JobQQsDxuhOuPwPXKwWI6QCSohjFb+DKM2VM2fUaqlV34JvpkUz2aoO+edX1L3/3LsJDfPcTS6Lt3DWvNd//2YePvHuUMEZMi5ADEuaPX6dBlioLECRScsl8rmzB0GPsopRs+SulAhnztylGYqt0K
*/