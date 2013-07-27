/*------------------------------------------------------------------------------
| This file is part of GameEngine.                                             |
|                                                                              |
| GameEngine is free software: you can redistribute it and/or modify it under  |
| it under the terms of the GNU Lesser General Public License as published by  |
| the Free Software Foundation, either version 3 of the License, or (at your   |
| option) any later version.                                                   |
|                                                                              |
| GameEngine is distributed in the hope that it will be useful, but WITHOUT    |
| ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        |
| FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser GNU General Public License |
| for more details.                                                            |
|                                                                              |
| You should have received a copy of the GNU Lesser General Public License     |
| along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.          |
\_____________________________________________________________________________*/


#ifndef SMARTPTR__H
#define SMARTPTR__H

namespace common
{

template <class T>
class SmartPtr
{
public:
    SmartPtr();
    SmartPtr(const void* const pointer);
    ~SmartPtr();
    void operator =(T* const pointer);
    bool operator ==(const void* const pointer) const;
    T& operator *();
private:
    T* m_pointer;
};

template <class T>
SmartPtr<T>::SmartPtr() : m_pointer(0) {}

template <class T>
SmartPtr<T>::SmartPtr(const void* const pointer) : m_pointer(pointer) {}

template <class T>
SmartPtr<T>::~SmartPtr()
{
    delete m_pointer;
}

template <class T>
inline void SmartPtr<T>::operator =(T* const pointer)
{
    delete m_pointer;
    m_pointer = pointer;
}

template <class T>
inline bool SmartPtr<T>::operator ==(const void* const pointer) const
{
    if(pointer == m_pointer)
        return true;
    else
        return false;
}

template <class T>
inline T& SmartPtr<T>::operator *()
{
    return *m_pointer;
}

}

#endif // SMARTPTR__H
