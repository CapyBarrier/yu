#ifndef YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_
#define YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_

#include "capture_t.hpp"
#include "perform_selection.hpp"
#include <utility>

namespace yu::select::detail {

template <typename ResultPolicy, template <typename> typename OutcomePolicy, typename Subject>
class selection_invoker {
    public:
        template <typename T>
        explicit selection_invoker(T&& subject) : subject_(std::forward<T>(subject)) {}

        template <typename... Clauses>
        auto operator()(Clauses&&...) &&;

        template <typename... Clauses>
        auto operator()(Clauses&&...) & = delete;

    private:
        using captured_subject_t = capture_t<Subject>;

        captured_subject_t subject_;

        selection_invoker(const selection_invoker&) = delete;
        selection_invoker(selection_invoker&&)      = default;

        selection_invoker& operator=(const selection_invoker&) = delete;
        selection_invoker& operator=(selection_invoker&&)      = delete;
};

template <typename ResultPolicy, template <typename> typename OutcomePolicy, typename Subject>
template <typename... Clauses>
auto selection_invoker<ResultPolicy, OutcomePolicy, Subject>::operator()(Clauses&&... clauses) && {
    return perform_selection<ResultPolicy, OutcomePolicy, Subject, Clauses...> //
        (std::forward<Subject>(subject_), std::forward<Clauses>(clauses)...);  //
}

} // namespace yu::select::detail

#endif
