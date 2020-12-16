// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SEARCH_PATH_HPP
#define BOOST_PROCESS_POSIX_SEARCH_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

inline boost::filesystem::path search_path(
        const boost::filesystem::path &filename,
        const std::vector<boost::filesystem::path> &path)
{
    for (const boost::filesystem::path & pp : path)
    {
        auto p = pp / filename;
        boost::system::error_code ec;
        bool file = boost::filesystem::is_regular_file(p, ec);
        if (!ec && file && ::access(p.c_str(), X_OK) == 0)
            return p;
    }
    return "";
}

}}}}

#endif

/* search_path.hpp
8fBJmAV3wInwLZgD34e58EM4Ge6BU+CXcCqM1ja/eFgIa8EiWAeWwI5wFhwEZ8OJcA7Mg6fBBXAIPA+eDq+Ew+H18Ez4IJwHN8EF/H8TLoR74GK4Dy6BceTlUtgYXgC7wAthT3gxnAUvhfPh5XAZXAGvgFfA2+CV8G54FXwSXg1fhtfAD+C18BN4A6zPdbwNNoO3w7ZwNewE18AT4B2wL1wLx8E74QR4FyyAd8NSeA/cfxhtjrvwVAYDCwokFFa2O/6/tzs2KfRp2yOyI7L9EZtC31+uDbKy/fF/u/2xd6HvP9IGOYzz5Bf+b7RDVv4qf5W/yl/lr/JX+av8Vf4qf5W/P/8XhUz6E/v/i9h1WQYA/AFzAGa6jAGY6TIGYGbkGADVecPHABi9LzQGoO+gIQNMGM75AbYu2owDsP3HBnWn9hkFHbbVRD+sz8hhtm11l/EC6F3HC+Q4xgus0XbMc5HqyGIkPY1v8DXSl6Y5zYABnXeQhptH9mJw75fGX2Tfvdgdcu4N5RhvsEPs+2Ef6judaNYpf0ncsk0ffkoS6w4iZY613aPCypz7HkOBOCeb/SP8Ehe3PvocGaiAfRR2yu9xWZfgzAvppK9wDkZBYsB2G/tC3236qrslBXR+9/xKOPw5GWprroOlaUrVfuZnxf1bTyKrWX5uNWHtxncknB3aZ2r3p2pfqktffar2pVb3B8J6wjfdc4L1gWegp6cv0/SrZkp6+po5HzXF9lHp158ZMacjSdxGe2pYPZxzQtgzyTJzQn6QeL/iixxzgLv0r3kkjOd94X3C5JNjLsQXEsZ7Ptf+fu3b/kxsPsQm1J+bnVeke+aZPb1MHNiIsCirOGu6PfbhffH/T986XxXLbc5FHfhG8Br4Nviqik0vKVmBcmPvYV/N7qM3Yw/eE39f+CL3KEnXfJxYS/r8Ka8dGRdck5LblDWwo82eJK+I+xKrLhYNrKOtQYwS1rRoXhQWT88qtVI0vDPFfr1VnzDaW6XBvUXC0s92erOySnMde67MScQP9s9xP7aNmIfxsDKy3zs3OchJyqQkaPaiLd8nvhl5P6Iv/Bj8NEUmO/Yky+a4GXIsMi3J1ufwd77jeLaKj0Q3TjL7/mo/uO4rchh94CuT7D7wzonl9/ZslVh+b8+GieX38dzpL78/5wP+8n3q59g6E16ev3xf+RhbZ84xwF++r7yt0XWW4zdM3DrJ8aCk8Hkn3ZJ+37wTdFLf2HUuunL94ronmukTt+9DbOUe6eVHr/cNtlI25dx2WQ6ru5tU1+tHpKvDeDiXumi7pGNBXkFe6Xgq8PElpcVyX54iz7EiImjXee+J7SGrMSHPQl5GEkP7bIhbf8bgx5o62ej5l2j2fMrKnxzcSlD31yA+yViw8nA/7p3rrDi3ut2Eo3UDfzGeQOudNPH/hNWZN4oViNuYORMP81wy9ZfbXlDYuz5LzP4ji+WcI63mpDLR1Fel04tkWJHu9xhWX8izMY/iY/LsZznHR6QvSc6zU8Y2kTelU8x50uU8k6wOnKcr9UoNK3jvtueCTNF9zp5FtlEPZKDrguSh72rP6eK+1neBX72Puc+Sy+8JFCgHyVoOUsL2BNLrqO8McTDOMc4jwdwLdj6jlzwRO5NX6MPuHc2niL3OMmpY8vsS8SBfILMpv7uS7fKLx0ARlqdaZBlOD43zEvvdjNXkTRU5B1mPuLx7EHbkfmUStJlrWUX6vadTBnzWOMSt3BJGZLl1K5/Y/Xp5K5VzjWDujM/xbC2SPXhS9T5IEpsNVn1ybghyHhLxjDX3XE+xPZ97mXGEEWVrmo6n6pBk7yPfOUnKFM8JbOxyxfHh7G/Dfs8pv1a2Ivebknw=
*/