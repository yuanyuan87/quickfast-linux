// Copyright (c) 2009, Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#ifdef _MSC_VER
# pragma once
#endif
#ifndef FIELDUINT16_H
#define FIELDUINT16_H
#include "Field.h"
namespace QuickFAST{
  namespace Messages{
    /// @brief A field containing an unsigned 16 bit integer
    ///
    /// In the XML template file this field is described as &lt;uint16>
    class QuickFAST_Export FieldUInt16 : public Field{
      /// @brief Construct the field from an initial value
      /// @param value the value to be stored in the field
      explicit FieldUInt16(uint16 value);
      /// @brief Construct a NULL field
      FieldUInt16();
    public:
      /// @brief Construct the field from am uint16 value
      /// @param value the value to be stored in the field
      /// @returns a constant pointer to the immutable field
      static FieldCPtr create(uint16 value);
      /// @brief Construct a NULL field
      /// @returns a constant pointer to the immutable field
      static FieldCPtr createNull();

      /// @brief a typical virtual destructor.
      virtual ~FieldUInt16();

      // implement selected virtual methods from Field
      virtual Field::FieldType getType()const;
      virtual uint16 toUInt16() const;
    private:
      virtual void freeField()const;
    private:
      uint16 value_;
      static FieldCPtr nullField_;
    };
  }
}
#endif // FIELDUINT16_H
