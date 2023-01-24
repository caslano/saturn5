/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07172005_0838)
#define FUSION_VALUE_OF_IMPL_07172005_0838

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type type;
            };
        };
    }

}}

#endif



/* value_of_impl.hpp
wTxdArLyshnlUoMcbJD3W7qjsC0OFsf0tuJEr+KnzYFdUQOW0D8AK6ja/Kb+qsT8rgBgaMsPN5CFbuptO+EdMuvNOzabwfx8jtQjKrs1g5J8yFYAQyxgiawdBYAllINtyHhj64mhZb8KZqcJ+sJmKnEV7JKK7A/Eunkr0J8s+KTjTd823Z+B/ioBzOhmIHmDTtlh7pP7EFUKtszjfHMctsLRWPnrrBBhG4SMWuhBskK0Ejt6I2ORLZbstrMhQyyFk2UhS1fYM463sj0ermxqi4AUtoIdUMpi3Fhtg7zbyBj9PflpEg4Gsp5xesc8l3b8z4D67Hgahvgp9Azv60kDS07ctpqjbfeY/vDMH6hmtn1pQENse+tfnI3fCZ3rjN907PbhtKOuHCe0HwXaj+L9rwF06FZotyHF9sqebpqhVmUjJWuCXA/kYBVoPZSVwBV49IXcodjIh1r+uXLDBmSFGuHdDdGZg5ea4KWXnGz8Wge8RwlvRCDtyHlJeT2CDNBj2NsSjCcmf2WMjhZ5orz3DQuQiCc+FYQn6cCTDHDAMBqefJCg4TgZpQ+Rn30Pi3sO7GR8cq5LGd/1c+WLSZpN8zriPbPYG9vj1xBpJpQ7k+asB+x8ijr+WLe5gj+m2VTXIUvyc3DI0uJ6bO+oeGTrGu+RteQe2UJHj2wkGnRxI85dspYuXLJ31A1xyVodcOGSxYdhKT8V5kSPb77u
*/