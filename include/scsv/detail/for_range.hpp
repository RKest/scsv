#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace scsv::detail
{
    template<typename Functor, typename IndexType>
    concept ForRangeWithIndexCallable = requires(Functor fun) {
        fun(std::integral_constant<IndexType, IndexType{}>{});
    };

    template<typename Functor, typename>
    concept ForRangeWithoutIndexCallable = requires(Functor fun) { fun(); };

    template<typename Functor, typename IndexType>
    concept ForRangeCallable = ForRangeWithIndexCallable<Functor, IndexType> ||
                               ForRangeWithoutIndexCallable<Functor, IndexType>;

    template<std::integral IndexType, IndexType From, IndexType To, IndexType Step = 1,
             ForRangeCallable<IndexType> Functor>
    void forRange(Functor&& functor)
    {
        if constexpr (From < To)
        {
            if constexpr (ForRangeWithIndexCallable<Functor, IndexType>)
            {
                functor(std::integral_constant<IndexType, From>{});
            }
            else { functor(); }
            forRange<IndexType, From + Step, To>(std::forward<Functor>(functor));
        }
    }
} // namespace scsv::detail