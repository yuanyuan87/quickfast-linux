// Copyright (c) 2009, Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#ifdef _MSC_VER
# pragma once
#endif
#ifndef FIELDSET_H
#define FIELDSET_H
#include "FieldSet_fwd.h"
#include <Common/QuickFAST_Export.h>
#include <Messages/MessageBuilder.h>
#include <Messages/MessageField.h>
#include <Messages/Field.h>

namespace QuickFAST{
  namespace Messages{
    /// @brief Internal representation of a set of fields to be encoded or decoded.
    class QuickFAST_Export FieldSet
      : public MessageBuilder
      , public boost::enable_shared_from_this<FieldSet>
    {
      FieldSet();
      FieldSet(const FieldSet&);
      FieldSet& operator=(const FieldSet&);

    public:
      /// Constant iterator for the collection
      typedef const MessageField * const_iterator;
      /// @brief Construct an empty FieldSet
      explicit FieldSet(size_t res);

      /// @brief Virtual destructor
      virtual ~FieldSet();

      /// @brief clear current contents of the field set
      ///
      /// Optionally adjust the capacity.
      /// @param capacity is expected number of fields (0 is no change)
      void clear(size_t capacity = 0);

      /// @brief insure the FieldSet can hold the expected number of fields
      /// @param capacity is expected number of fields.
      void reserve(size_t capacity);

      /// @brief Get the count of fields in the set
      ///
      /// Group fields are counted individually.
      /// A Sequence is counted as one field.
      /// @returns the field count.
      size_t size()const
      {
        return used_;
      }

      /// @brief support indexing the set
      /// @param index 0 <= index < size()
      const MessageField & operator[](size_t index)const;

      /// @brief Is the specified field present in this set?
      /// @param name Identifies the field.
      /// @returns true if the field is present.  Returns false if the field is
      /// unknown or doesn't currently have a value in this set.
      bool isPresent(const std::string & name)const;

      /// @brief Add a field to the set.
      ///
      /// The FieldCPtr is copied, not the actual Field object.
      /// @param identity identifies this field
      /// @param value is the value to be assigned.
      void addField(const FieldIdentityCPtr & identity, const FieldCPtr & value);


      /// @brief Get the value of the specified field.
      /// @param[in] name Identifies the desired field
      /// @param[out] value is the value that was found.
      /// @returns true if the field was found and has a value;
      bool getField(const std::string &name, FieldCPtr & value) const;

      /// @brief Get the identity information for the specified field
      /// @param[in] name identifies the desired field
      /// @param[out] identity is the information for the field that was found
      /// @returns true if the field was found
      bool getIdentity(const std::string &name, FieldIdentityCPtr & identity) const;

      /// @brief support iterating through Fields in this FieldSet.
      const_iterator begin() const
      {
        return fields_;
      }

      /// @brief support iterating through Fields in this FieldSet.
      const_iterator end() const
      {
        return &fields_[used_];
      }

      /// @brief identify the application type associated with
      /// this set of fields via typeref.
      void setApplicationType(const std::string & type, const std::string & ns)
      {
        applicationType_ = type;
        applicationTypeNs_ = ns;
      }

      /// @brief get the application type associated with
      /// this set of fields via typeref.
      const std::string & getApplicationType()const
      {
        return applicationType_;
      }

      /// @brief get the namespace for the application type
      const std::string & getApplicationTypeNs()const
      {
        return applicationTypeNs_;
      }

      /// @brief swap the contents of this FieldSet with another one.
      /// Fast and no-throw.
      /// @param rhs the FieldSet with which to swap
      void swap(FieldSet & rhs)
      {
        applicationType_.swap(rhs.applicationType_);
        size_t count = (used_ > rhs.used_)? used_: rhs.used_;
        for(size_t nField = 0; nField < count; ++nField)
        {
          swap_i(fields_[nField], rhs.fields_[nField]);
        }
        swap_i(used_, rhs.used_);
      }

      /// @brief act as a factory to create new fields sets to be nested within this one
      virtual MessageBuilderPtr createNestedBuilder(
        const std::string & applicationType,
        const std::string & applicationTypeNamespace,
        size_t size)const;

      virtual const FieldSet & getFieldSet() const
      {
        return *this;
      }

      /// @brief For DotNet: get everything in one call
      ///
      void getFieldInfo(
        size_t index,
        std::string & name,
        Field::FieldType & type,
        FieldCPtr & fieldPtr)const;

    private:
      template<typename T>
      void swap_i(T & l, T & r)
      {
        T temp(l);
        l = r;
        r = temp;
      }
    protected:
      /// Application type as set by &lt;typeRef>
      std::string applicationType_;
      /// Namespace for the Application type as set by &lt;typeRef>
      std::string applicationTypeNs_;
    private:
      /// The collection of fields
      MessageField * fields_;
      size_t capacity_;
      size_t used_;
    };
  }
}
#endif // FIELDSET_H
