#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/xml_woarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_woarchive :
    public detail::polymorphic_oarchive_route<xml_woarchive>
{
public:
    polymorphic_xml_woarchive(std::wostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_woarchive>(os, flags)
    {}
    ~polymorphic_xml_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_woarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP


/* polymorphic_xml_woarchive.hpp
wCggPnER80JB4+dri4nLsDEHmUn6HV8F2Ix2D7IVSb6NLcdHlLYdnKcFuJQ7+VgBeEfhi4n3/x6RQBNVtbXMfQan0dvWVbTEluJNxGEGW593+nWHp7sLKBXc9vpQNWJOG3MbnGdCVYq24caxfBtmu0tH2N2Zh72RRZlne7LoRmS6yw93+CYQACtJ+T+OLXW9M7Bn8Cw0kyMSg9PmSaVzkYz7iqred+UQikk6zwnrQPOeHlwbnNWPt/6aHwX/Y4Sz0/TiwjibvhccBUKI2lK8SiRATbFvNBP18Rfwr67Rx9Wr/gX4Kt2tbcLdEdOS+MelhX/TX89RrTVK3u+VBrTI50rjbC6W+mvfadWkHqE/AMFYSeRdyMjXtqM2RbbRdoE4PffH6sAJy/zV+2f050Kz3EsG99IHP32Doi+CcNCTQnTw2DjbxsgfJohDcvT5E3lUahqLYsj9ZpxyJ/53pB5/6azvv0Mkh4Pupaa9KVrTstXcZAE61H+Io04ekxQNneifImVj5EwUDu5Sw/RyZ4dB74MFAX8mmdAPyquhBy9yADVM1+g+NMa5d1Ju/Iec29nIHcO4Z2I4OiW+z5+AJlByliT/MF6Sh70vyWchmeK1c+KtByXxNHkNd3eX5Oc6ivH8z3IbJ7eR5Pe3SOm/S3JMU0kOHJHk7Tbu0KdJhw8kSCNlkuxRyZVOSX5QGknsJ4280EGSb5DkbSrZCzqBeGy0vj1FcHpuC066DEljw6XUs58zJ+48LbKNpo5Ji4N0TGI1OiZ7x9Ex6Q6WD/z5j47D8Shp9xbt1vvhtH9/v4H3b8sYpGxAioVPAM+7LyJXv0KnE9z0WXyniL/t7qfEbeB04fs9+H6SPqBP5Udij+6KNLgTr48zuROICQeeRGSbDHHnlFQeQ0VbAaviYI0vqTCxYcjXM9qLVmsqsRXOa8HXxd2YeUn/F5r951j6DyT+fXi8DUO4ExIk7j1H28RD0W/+rs4oFqOI/mI7yyi2NG/MKAz+3jsRQfwxcQzdl++OkAuuinxitopvOaBwr7j5fQe2Jiw6Jdwd9jvi+naNFGPNLP3NzUHdFXFMgXLgkJTHGlqBHm4IQAjP3oJsG2r3iBQ9kP5YbtFJG9SmLkdQi5y1Sp3UGT/QSZ2Mn+VTFInYK5Kpw5fQgrYJvMUmehwutX43sCxXWR9p/l5pXt93uuGtIqvxzMZGfITeD0Z8vDZcyb2OIOKjljhoVJytgFwx7Ib3a28udClXqvnc/T3N52b8LDdI3k4SfLG6n5pPlP5P9s4DLopjj+NHOUDaoXKKHTtqrKjBgnIKeijYW+y9x1jA3vA0ghvsMeozxqiJiSWWZ0E0CqJgF8Xeu3tgQaKI9d7v/5+94yzvPfN6ufHjcDuzOzO7O9/Z+f9n5j/1Hwm5XhjgDxKWNSwGDgfKFSDrkRIqx6Rd0NKTVJyQx9cDc7EELLKepK5qztCPM/S1ztBPZDjWnGFR+chDytC4xZ6Ws8ykIUpDjodmZk8c0/6M25AyTOtN8wkvoMJQmOmGYjCkNpaRYffIETgNVUgJVKEpRWBXBIZbdv/LOMuBTRGohCz142trUZZxgaKFvVtTzAHfccwyU6Q6pjX4UfvDAw4NcZ7sAR0wpRzTgyJu1hRvumIOpqTeQ7yk9v9SufdPsujey+CQbrsxT8PSkUZtLZ3XNCBo+lUybpfpBQN3eTNc8CsvfnlBSRTTNIDWFSlpH3+GtCVcQzElELFBidhGESM53c/ELZRWbuHJUdwCbbBECsOYpi6IWqxcNJUuCuSSxsxQSjrtMZV0/AxR0u65JVUpufagRVGjlRQaUAovuaE4wtO72EAWxWwtgVkoyZoZlzkSMWw=
*/