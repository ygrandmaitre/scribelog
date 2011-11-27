// Copyright (C) 2011 Yann Grandmaitre
//
// This file is part of scribelog
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
/**
 ** \file fork.hh
 ** \brief Declaration of Fork.
 */

#ifndef FORK_HH
# define FORK_HH

# include <unistd.h>

# include <list>

/** \brief Define \c Fork class.
   **
   ** A very simple C++ wrapper for the fork command.
   */
class Fork
{
public:
  /** \name Ctor & Dtor.
   ** \{ */
  /** \brief Construct a \c Fork. */
  Fork ();
  /** \brief Destructor a \c Fork. */
  ~Fork ();
  /** \} */

  /** \name Accessors.
   ** \{ */
  /// Return the pid.
  pid_t pid_get () const;

  /**
   *  Test whether we are in parent section of the code.
   *  Return true if it is parent code, false otherwise.
   */
  bool is_parent () const;

  /**
   *  Test whether we are in child section of the code.
   *  Return true if it is child code, false otherwise.
   */
  bool is_child () const;

  /**
   *  Execute an external command.
   *  Conveniently wraps fork()/execvp()/wait() sequence of calls.
   *
   *  @param cmd_                 Command to execute.
   *  @param list_argv            Arguments list.
   *  @param wait_child  If set to true, blocks until child exits;
   *                               false otherwise.
   *
   *  @return If wait_for_completion_ is false, returns child PID;
   *          If wait_for_completion_ is true, returns command exit status.
   */
  static int fork_exec (const std::string& cmd,
                        std::list<std::string>& list_argv,
                        bool wait_child = true);

private:
  /// pid
  pid_t pid_;
};

# include "fork.hxx"

#endif // !FORK_HH
