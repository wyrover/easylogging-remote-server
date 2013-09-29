using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace Lib
{
    public class RequestBuilder
    {
        public RequestBuilder(String user, String password)
        {
            this.user = user;
            this.password = password;
        }

        public String buildWriteLogsRequest(Int32 level, String logMessage, Int32 verboseLevel)
        {
            StringBuilder strBuilder = new StringBuilder();
            strBuilder.Append(createKeyValue("type", 1, true));
            strBuilder.Append(createKeyValue("level", level, true));
            strBuilder.Append(createKeyValue("log", logMessage, true));
            strBuilder.Append(createKeyValue("vlevel", verboseLevel, false));
            return buildRequest(strBuilder.ToString());
        }

        private String buildRequest(String json)
        {
            StringBuilder strBuilder = new StringBuilder();
            strBuilder.Append("{");
            strBuilder.Append(createKeyValue("user", user, true));
            strBuilder.Append(createKeyValue("pwd", password, true));
            strBuilder.Append(json);
            strBuilder.Append("}");
            return strBuilder.ToString();
        }

        private String createKeyValue(String key, String value, bool appendComma = false)
        {
            return "\"" + key + "\" : \"" + value + "\"" + (appendComma ? ", " : "");
        }

        private String createKeyValue(String key, Int32 value, bool appendComma = false)
        {
            return "\"" + key + "\" : " + value.ToString() + (appendComma ? ", " : "");
        }

        private String user;
        private String password;
    }
}
