/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_IN_05042005_0120)
#define BOOST_IN_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/in.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::istream&
    in(std::istream& is, Sequence& seq)
    {
        detail::read_sequence(is, seq);
        return is;
    }

    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::istream&
            >::type
        operator>>(std::istream& is, Sequence& seq)
        {
            return fusion::in(is, seq);
        }
    }
    using operators::operator>>;
}}

#endif

/* in.hpp
F7swUBWMVXNDm97OY3NWYaC/yzog7apBk2WjjeXxXZoGZSLPZeN5u6w9N0LaNJeFYT0Ije5frxIaFGbwPfrGJo228yVJI3NYq5333cTGtNv5fAfGbOeJCZsuq4J9Yl1hcM6lfe7bFp32ufimbTrtcx8jdKwA0nffTNDBcN905Dba4R1It8Y7YuKbawwdg7qcK4gx+r9RzuYtkE4jd5tx6m7ZjZFmwCjrpYNwJ9exf9z+Voip+6TZZu9o0aR85L3PrSndlPsOSpvmZp663S2aFIzfyqKDYDNe2W2QTiOlmjn0EEOmOJSxeNsOuqwH3l93YaAupN/eTmCWDi4M6DdXkT6432zfHjED+83fENPdb558B6QP6jcgjGAG9puziBvcbybuhBir3zyP0Ox+s2sPpaNcwYs0u9+M35nQrH5zltDtfjN+F6QP7DfPQ0x3v9l1V6QP7DfnEGP1G5yzb7FXYDb7tfGjjCGEdx6ERmM+Yn5SIw91nYzVk34a03hFidhzBjbvzZ3u2Vhtm29gk1WAwX3GE9sMzurC9PrSqte4QmE5FwxeX7iJ2QWtKX3JxVY+7q2NDVBBzSyKlB3JwtDaHdUZw8DNLPcdkUFLDF9F/xSlg6iHyDi18sxB6dOKjvonSg/FolIq2qvMs0fGAr9IfTe99rws8DZMxoZ6CJwr8gT6QgDpjx/W5Go5Ds/40Zl81juazCSek8PE4M0IryU/cI9Fdd6Dhw/CyPjSort6Rx/GZ6rZmVjkWZ7NK0ABreHNucU4gA+mLVnXm2laVXoB3rd+WQScHyZcKpoG3GzRGJWPHraxwoZ9bqMnfLtQ5g9tXOMi2HQIwGqZjxzpxFpl/9DGCW8OBKJfzqiNE5fian+j48J24+QWAnEv7cCJ/lyDDdztd3TgtlZna8848z06cH18Xz3fnNlp47ZWm0IxHtL1bEyTQbrB4fxn4FRSb7j1xPHyp516vDyuvybus5F2fkzTVnqQ7uu0HkvnW2MpLtysioPkWseSyLbIZM7xKejXOi2O42Xi/ko8hz3irLe2AdPOJjhzw6QDt1zTvbmN+cVpqKnXdL9wa7WejGjOor8NK4lwD7zQ663XKU10u7xq2MKICQ5lxCOd9Nn1zQ2997MwW+vkXDRK6Sp/D8Yu7aKDk9cQiU1MMNiX0Ve3RVeJh3C/sqNNB1fp2rrB8C/bSTA4DjDvqUXHK3mtr7oexUjfcKR/tk1fXyNr+eS4TW+/67dbGIzLpOao61O6GFzm+PtdB11E5K7tIAw5527Qxi0undzU9KEbUnrdoOb4bdO3VqUEY++zi2KUFgT3Pm36E3sba8Z+4081vbY3hGgmTc/CuKetsVm5ScEj/5r93fsb60cOGvfxnzo9asTcKN2g9FwvEb6eGd5R3wruk74A+cNYbV9y4tBkbcDTrIv3ukOd62f6KG8SJa8/fkEnA5Lr3gGNOVVi+qGGf8rmN7IcNZgHUn5hXqqlyHnmQYAxhShe15aveLF+AZGPpdf8qV02eb8bAyYHTANo5D2Y8iBarNffONhgH+I604Gs+zTgzQJU3R9il61rZ/rjw89fh1GqGlpGvAhKh3X4APjR1w0CZCNehIVDGObzbWGWVlt3GGOETu7Xfixp6AxUmzcvgXSoK841AzCzbmnuyd8/LnD4ycgdx97raxq6hxr0n5v09eW5eUgSu2rQf3gDpPc2BeZE4+OOc8gNJZ12WcGP45/S5b2epG/b9H5d0JDG7LpRJwbUDhpzoRvTP23E7Thz4wGYpj3xDmz3TQQO/Yzx+fn6uZiCagEol02I5/3/mEvukoXrzv3h31TirN5uyOrCYDY+jTt+sy4cLmxY5sc6cTRPyP4=
*/