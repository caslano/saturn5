/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_0137)
#define FUSION_DEREF_IMPL_07162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<joint_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
1IPNZ5pXi4XtP7EdewlKTheIGALb5rHqL208nn+72k3PTNvmM9Ruqtdm8cw2342yqUPe7cpP71If83MD/Nl/w2P0U9T0AWhCed348TCsToD9YrF5RvkKdft6fBBmRA8KbT+xyPTdwFU2d+8dTfr7TLSzNSKp79tOSNnrik+AWWyy8ABWGytkVw2bdt7qshoYKeAtxpL+bp0ojyEVvETe9yuVfLNTtXwizIjyVmk0WpO+3U/It2IzyKWiqZfVfDlS3rfjXfC9gDjoKuBkeWzJccXcHWu0WDehr8XwJpwtlF9Ip3SOH35CyWDxXdArHjFkpPK3O7s/x42Shb40FdJLJoAGwV+h3M+nPeEav+l3SOe6RZ5G9lQau2cHCG/uHdPYvV+Q8jZ+f3qcHSOfIQvUlwvTeJ7te8eqLy8Rz2z7XSqZKKwRZ22gp4aGwPHcpA9as37yRw0+duTg4frZlwtkGXCGYyDEBiyJjuB3jx3OI0OywUqu20V5nmZdqoardeZ7oqySSBwcsI6XCmNMYW8p7IgkptqxVmFDRCi5OpW+UqUP4F6vyXM0XUV9Gnlj1ZD9QDw3akocDvqXQBSHkihnD/8red7sz2qRZ3IYjIAch7vCaFzoIMrfiheZ5pfbRdAyDkvRWZxfFTYQdibhUuIRUtwSCs8XdBp5wSUU37MV3qRHHQupcoIqn+mhR3X8oUbgMIFgRUYn+bAhFRuQpH+lwI6pC9VOKQ7VisMTNRVQeh1fEmh7Tv1EvqPrEhDJSYzao0TkDT5uUJ5ikYekqySqRE47lzZB5BkOLgzDw+WwRThlNKtUWHkqNoBVqrIXSywEsdUG4rQ1ChcWIbq3y5hbmvbS08+z9BI8bTwLKZpFEm+8Cwzyq8b5JTVGntTKDaipHBUL1wh+UrnzxDNHiDjVI0LV0dopoxJQxbh+VvImmSeUKAEVUT5O72yGwpLiPyBO4s8GqDLaNM5H8rIfYYlK6e2a5Etf0e7UWZdFFD5MPctZPACONvKeqeGDFD5CmCVE8SCPEdX+mqbwweIYUDXZ/mQevc9FFNZDYaLNYjskQmd9FDaY7JgwFtWG+SIACAxQdXgR89GiUihfR1bq8jyb8hieozwT9cvO0SbzEC/XURnG+EDvYazA+aCIMq+VvYPExIEmPC01Wn+2QeIwnowM1XNmAKyePZ2wIXBxuwR1216CcHGWi8r8W6QPrg9TS9hoOjMiMT4yNOqD6nlf5BkU4sqhHHHZKPX8sxqWWoB6PlPk4cf+6HmSm5/FeA6MhPiK+MLUsJ48J6XnEVhJVGZN8u14QUO0W4k++QIXB8QZMDWJpp4CI/6dKt775Ip4PGH4KAezm5uXjx+I7vwH9ioYROXERDlQiCxnkEo/RaWDE0Wtln6sShfJcPZb+eMEaezjZ6VAG0mera4Uz0BqdXQStDWunllqPgPnq9ixCluQglXHkuVNUuXJOlSofeGY9sxWPWNAPVV6TL3xTONdbchSSnHN5fk8g5GNXpC2z/5zDN9RJGT477dv7h2JxSE3PlXS+5mlygDu6O9nE6VXx/T0VYI3iWgkOplXfpDyb1yVmWxnUsNnR6vn5qv3mojWRWAcVOmfJtMhOZm+NKbkJlajp09T6TWiwpT+YJTSocIwzio9Mp3qhUGzknPQAlWWuEG5NK7z9nGFVYgKkEzlZxjl8UokSEZNWrwihGWmPFeWSNL6SNASdxxGuLyp9OdleigB0Qz19JkivTYkDlJBujo/Xy/ShVc4U2kfCL6cJi6nUs8zkS8mWq2XO06kV4ti9fShIj0crxf3sCfTl0dlel0MytLyv4zpsD1dEdLSr8d0UYyWvgjLL4vAkV4tfaRIhwU=
*/