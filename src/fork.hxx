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
