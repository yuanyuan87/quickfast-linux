// Copyright (c) 2009, Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#ifdef _MSC_VER
# pragma once
#endif
#ifndef MESSAGEINTERPRETER_H
#define MESSAGEINTERPRETER_H
#include <Codecs/MessageConsumer.h>
#include <Messages/Field_fwd.h>
#include <Messages/FieldIdentity.h>
namespace QuickFAST{
  namespace Examples{

    /// @brief A message consumer that attempts to produce a human readable version
    /// of a message that has been decoded by QuickFAST.
    class MessageInterpreter : public Codecs::MessageConsumer
    {
    public:
      /// @brief Construct given a ostream to which to write the interpreted results.
      MessageInterpreter(std::ostream & out);
      virtual ~MessageInterpreter();

      ////////////////////////////
      // Implement MessageConsumer
      virtual bool consumeMessage(Messages::Message & message);
      virtual bool wantLog(unsigned short level);
      virtual bool logMessage(unsigned short level, const std::string & logMessage);
      virtual bool reportDecodingError(const std::string & errorMessage);
      virtual bool reportCommunicationError(const std::string & errorMessage);
      virtual void decodingStopped();

    private:
      void formatMessage(Messages::Message & message);
      void formatSequence(
        Messages::FieldIdentityCPtr & identity,
        const Messages::FieldCPtr & field);
      void formatGroup(const Messages::FieldCPtr & field);

      void displayFieldValue(const Messages::FieldCPtr & field);

    private:
      void newline();
    private:
      std::ostream & out_;
      size_t indent_;
      size_t recordCount_;
    };
  }
}
#endif /* MESSAGEINTERPRETER_H */