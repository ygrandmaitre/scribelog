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
 ** \brief Inline functions of Fork.
 */

#ifndef FORK_HXX
# define FORK_HXX

# include "fork.hh"

inline
Fork::~Fork ()
{
}

inline bool
Fork::is_parent () const
{
  return pid_;
}

inline bool
Fork::is_child () const
{
  return !pid_;
}

inline pid_t
Fork::pid_get () const
{
  return pid_;
}

#endif // !FORK_HXX
