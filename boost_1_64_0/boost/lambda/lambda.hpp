// -- lambda.hpp -- Boost Lambda Library -----------------------------------
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://lambda.cs.utu.fi 

#ifndef BOOST_LAMBDA_LAMBDA_HPP
#define BOOST_LAMBDA_LAMBDA_HPP


#include "boost/lambda/core.hpp"

#ifdef BOOST_NO_FDECL_TEMPLATES_AS_TEMPLATE_TEMPLATE_PARAMS
#include <istream>
#include <ostream>
#endif

#include "boost/lambda/detail/operator_actions.hpp"
#include "boost/lambda/detail/operator_lambda_func_base.hpp"
#include "boost/lambda/detail/operator_return_type_traits.hpp"


#include "boost/lambda/detail/operators.hpp"
#include "boost/lambda/detail/member_ptr.hpp"

#endif

/* lambda.hpp
wo8/emjLvFO3J/3fsvd8qvaY182WOzGXla6+u83njx2Im/ne9uVP9Ti1e895nr0G7mNs8tkj7kOdpEzqmvUFJnKPtzv3eAcB+3OPc69n7Qzcz/TagnYzvYFMbxB1jAYDU4HnMr3zqVs0genmAycDJ/Fuw8nAcu5dVzP8RdwrXcw90jrukd7IPdI7gWOoC5QH3M490hcYfyf3Sl9muq/z/RvAocC3gTnAfdZ7pUvFtSXX1pt8dKku5F5uIXU8i6ijV8y964tZ7hLqRJUCL+Re9VzubVdyb3sZ97ZXMN413Nu+FlgBvJHv13KPewf3uN/m+3e4190SDF1k5Qu03ncC1lj5A2uB8/m+EugGrgcuAG7m+4eBC4Fb+PyZnB1wTcd16CZ+A8dTDpeyvpcAw4CXUZdsKXXzlnOP/nLqiF0BnMb36syB7bMb0/c9GzHED8F4NpLIM5AknpGk8mzkDNvZSDeTc2Gui6x0U+t1tODwzDOFzayfh4Bu6hZfCnyUOqqPsR5+A7wbuIU6aY+zHp4A/pm6dQeATwK/AW4DtkFezwAzgX8E5gN3AOcCXwD+BPgi8E7gLuAm4CvAJ4G7gc8AXwNuB74BfJ/pHAFuB34JfAvYwlGvK9cB+B7wDOA+YAZwP+/6/AA4DPghcBTwb8CJwI8or23qu415F9t7nMih3h2iruCnbN9HgEXUfSyhbuUi4NfAJbzb9ZfAY8DfUtfy9wz/FO98/ZMFwHf4/E8+J5n1zxlA6zkH6ABOAjqBFwCtdGYAQ4A/4fMix4nPNA4uhV4bcO3ZOCMAbQfpzjeyJ9SfcdQBbwFtsQjPbwI9Zx555zQ896jGuzUgz/nHXvy9AnhgtbPBOcgt+Y2fhWRMRHhgPvAAcC3wKHDbpy4j8jpng/ORFLw7MPH4OUnpJP9nJa7JyAuYDlwFHIm4+fh7DWg9ngvwjDOUkz4/eXMK5A5ai3Rcw5H+VOQLWgHaBPKcrWyfinAg64xlyDTvc5ZtePY5a8Eg5DCiHoceIzALpDt7efNc/fnL/eAlfDrymB74WUzeecfPY6KuDDOyQNNBdaCNoO2gA1f+d53JBF3QBV3QBV3QnW73bzj/B1kXef3w+//a4/for7PuF+lr2UmNGznaOisttGzkRadf/Kf2xNzYy78GbFVVIoDoD7S33R9YyrVGpmetDdoYC/2f+jOmUZMmyT0ghUwJvNSq8+VmSGFpFCiA8yH77+br91z8763kdzLx/tju1yO3F7xU0uHaI58/lfP4s/72aP677FvzDMqadZDh2fvQrC1juLZsR7u/dK4p+3BNuQq4dRl0oUBqvXCSdjyu+jn0SdvwfLssON8MuqALuqALuqALuqALuqALuh+fc4Fmnd71/5x5padG979jEtZ+1EFaQmWSDVy3rwSdZ+kgxcjaPQ9rdiNG6R6VLawupC4ldeTatrbCzVZ6M3HyPMMIB0ewvNXfOx/TQDeouMJ9XKcpStIoAY/Rer0kxqe+EOOLXorSvzEljQyNbpIuf+rWUXf1mPhnaXSVdHkjro/e3dcSJluju6TLu7xyVtVxvaAw4bsS+gitdHpLvvkzvjCg11GKaaArNc/zW+LxwAjJr9zIoK5pii1+ijY/xGd5rfCdbeE7e+dHncjqmnleOpFnR2/Gc6kT59TW/dYdjt8n0CnJYD7Ul7LlY+nIOowJ0Z6wnakLNT5A/cJ4u14U27FGNwrtyFenkG3LVz+KbcZbP0q1BepHMSzrON5LP4r1xnRTlC4V5Mt0O6uwSubeOoiUrV2n8CCNMn5vUs8AeKH1G/etVX8uHMVLKjX9WrXDlyT89dBfaaXrw0zP3o6FFzUuvCr+t5qePrFDnls=
*/