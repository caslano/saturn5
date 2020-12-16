/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_HAS_KEY_IMPL_31122005_1647)
#define BOOST_FUSION_HAS_KEY_IMPL_31122005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl;

        template <>
        struct has_key_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : mpl::has_key<Sequence, Key> {};
        };
    }
}}

#endif

/* has_key_impl.hpp
A9u2m7dXqeP4+8wzL+CnpI1X8YfSyhv4/F+YT57BXTIp9vubwxmyJZ43vFS28jJ+XobF/eC9chAPDd+LZSjPYrvsiseJl8t2XsavS5M2ddz7AWukHuGFMlK9jGMe9JlXcO0O888beNyv3FfWuuA8maZexKulg1fxLtnEG3jgr42fZ/Ac2cwLuFLW8greKRt5A/f7jbXgER4jq3gW22UZL+D7ZD2v4J2yjjfwgJ3WmmfwDOnmebxUBngZD3vIXMXjx/1/a35exbHxO2uhnt9lHR6xXryKK35vTngNr25Kh63xvO2RDlc/LR2GZjnetmc6bFdP7ZUOl8oOXsHf750OTXGfT0/7t5rSYRgP+6RDMeXcE4xnv3ToOCgdlvDoBekwUcaN0R4vktG8hBMi52tTxKulQ72KP5JpvIFfT+tfm1xLOiyW1vhc/JQcxKv41hemQ0Gb7IvSoUua1Iv4QdmVNWZ8x6HpcKF6Dc9+sbHxIh78knRYxnN42EvT4VpewPtlOU+NSIc1sorXcOxh6VDleRx1hK/xzJHpMOOodLiZV7AuNd7AjpHpcDsv4fOPTocVJ3C875h02BZfd1Q6HJ5Nh7XqmRPSYa5MUi/iDdLNa7jP2HQYwSM8T4byAi4dlw5559Zw9/Hp0KaewrEywHN4iYzkJbxJhvEajjvJXDm3ggtOToeGeuaUdDhf6ryIPaemQ06bBl5yejpkY8dVU6wfL7Wl/X80p8NUHs5Kh49PNS88f046XCzjstrgdTKJ1/AB2c7Dq9PhpbKFZ7Fd1vMCXi7reBk3yBpew9/JJp46Nx2Ol408h5fIZl7C62UHr+EDspX7j83Di2Utz2KXXMiL+B4Z4GXcIB28hr+TJTx1nvmUZTyHF8gqXsJPy3JexXukm4fXpEOztPEMniPTeAE/Koeanyr+RjI8NT0d9s2bB57DWR3GzAud5kHW8TLeIut5HYfMMg88hS+SjTyD58pmXsCVsoNX8UeynTfwsNmeC57Ffmkaax5wRFc6lHkZt702Ha7i2fPT4auyiDdwTY9njed73bsM5TUc2W8v8tRAOrQsSIcKr+AxizxTvIzvWuwZ4XU87ALPES/ikovMDy8VzY+08greKsN4Hfe+2PPOIxwj43gOZ8toXsDLZQQv49eljdfxGW+093iEE2Ukz+MHpcQruOoS7y9ex4+8yXPKs2/Wj2wb577ekg4zL0t7tqzvOzxrl3te1Et4nUzgNbxfsjy809ffnQ57aZ9ZYQ/IHPUCtrwvHYJ6De+XvHpYZX/KUp7F6VLkBVwph/IKfksiXsfGB6wRL34wHT5ctna8gRNWm3Oex41S5XUcdaV14Tl8RG7mmQ+5vtR4AbfK7Ty1Jh1O+nA6DDfOMt71Sdfl2U+nw+slF987fkMKvI4Hf8Z88gzOlQwv4qRr0mFn7HiNTOVVfFAW8bAuHY6SFTyL/TKKF/Gmz3kX8fznfQ+SvXgZN0jgNXxAGtYrXOt9Iqm4H2yX4byAK2VnvNZ4q9R4Hfe+zv3yCMdInedwsWzjZdwpU9176gtp/72r+eLRentJsjyPF8koXsJvyARex/1vMFc8wjFyKM/hYsnwEr7uS+aBh6p3khR5GTfIHF7Dh6TAUxvSYbzkTnRdfJtM5WX8jiziDTzwRv3wDL5BAi/jI3J7PJ6bvNtlJy/hyI3mhOfxk9LgNTz8y/YJz+GUr9hLvIy/kG089dV0eI3UeRF/JYe6VnRzOhxwi30Y94k7pcKjr6XDFySlTR0v/ro15RUMm+wxnvqGOZbhvIi3ylLnNnDON82Degmba9rFjtfcZi14cbNnSubw1HfS4QgpxfsWz5cyL+LVsoJX8V65iofvpsM=
*/