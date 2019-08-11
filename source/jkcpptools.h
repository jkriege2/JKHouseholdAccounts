/**
 * Project: JKHouseholdAccounts (https://github.com/jkriege2/JKHouseholdAccounts)
 * Copyright (c) 2018-2019, Jan Krieger <jan@jkrieger.de>
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JKCPPTOOLS_H
#define JKCPPTOOLS_H

namespace jkdetail { //adapt to your "private" namespace
    template <typename F>
    struct FinalAction {
        FinalAction(F f) : clean_{f} {}
       ~FinalAction() { if(enabled_) clean_(); }
        void disable() { enabled_ = false; };
      private:
        F clean_;
        bool enabled_{true}; };
}

template <typename F>
jkdetail::FinalAction<F> jkfinally(F f) { return jkdetail::FinalAction<F>(f); }



#endif
