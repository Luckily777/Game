1 #include <stdio.h>
2 #include <unistd.h>
3 #include <iostream>
4 #include <fstream>
5 #include <json/json.h>
6 #include "tools.hpp"
7 #include "database.hpp"
8 #include "httplib.h"
9
10 //����Ĵ�����������Ự����¼��ע���ģ��
11
14 #define START_TRANSACTION "start transaction"//��������
15 #define COMMIT "commit"//�ύ
16
17 class AisSvr {
18 public:
    19     AisSvr() {//���캯��
        20         svr_ip_.clear();//�����һ��
        21         svr_port_ = -1;//������� ��-1 
        22
            25         db_user_.clear();
        26         db_passwd_.clear();
        27         db_name_.clear();
        28         db_port_ = -1��
            29
    }
    30
        31     int OnInit(const std::string & config_filename) {//���¶����ʼ����������Ϊ���з���ֵ
        32         //ԭ���ǣ����캯��û�÷���ֵ
            33         //1. ���������ļ�
            34         if (!Load(config_filename)) {
            35             LOG(ERROR, "open config file failed") << std::endl;
            36             return -1;
            37
        }
        38         LOG(INFO, "open config file success") << std::endl;
        39
            40         //2. ��ʼ�����ݿ�ģ��
            41         db_ = new DataBaseSvr(db_ip_, db_user_, db_passwd_, db_name_, db_port_);
        42         if (!db_) {
            43             LOG(ERROR, "create database failed") << std::endl;
            44             return -2;
            45
        }
        48             LOG(ERROR, "connect database failed") << std::endl;
        49             return -3;
        50
    }
    51         LOG(INFO, "connect database success") << std::endl;
    52
        53         return 0;
    54
}
55
56     void Start() {
    57         //ע�������û����֣����룬����
        59             std::unordered_map<std::string, std::string> parm;
    60             UrlUtil::PraseBody(res.body, &parm);
    63             std::string name = parm["name"];
    64             std::string password = parm["password"];
    65             std::string email = parm["email"];
    66
        67             std::string school = parm["school"];
    68             std::string major = parm["major"];
    69             std::string class_no = parm["class_no"];
    70             std::string phone_num = parm["phone_num"];
    71             //1.2��֯�������
        72             Json::Value response_json;
    73             Json::FastWriter writer;
    74             //��������
        75             db_->QuerySql(START_TRANSACTION);
    76
        77             //���������
        78             db_->QuerySql("savepoint aa");
    79             char buf[1024] = { 0 };
    81             bool ret = db_->QuerySql(buf);
    82             if (!ret) {
        83                 //1.��һ���Ͳ���ʧ����
            86                 //1.2 ����Ӧ��
            87                 response_json["is_insert"] = false;
        88                 resp.body = writer.write(response_json);
        89                 resp.set_header("Content-Type", "application/json");
        90                 //1.3 �����������
            91                 return;
        92
    }
    93
        94             memset(buf, '\0', sizeof(buf));
    96             ret = db_->QuerySql(buf);
    97             if (!ret) {
        98                 //1. �ع�
            99                 db_->QuerySql("rollback to aa");
        100                 //2. �ύ����
            101                 db_->QuerySql(COMMIT);
        102                 //3. ��֯Ӧ��
            103                 response_json["is_insert"] = false;
        104                 resp.body = writer.write(response_json);
        105                 resp.set_header("Content-Type", "application/json");
        106                 //4. return
            107                 return;
        108
    }
    109             //�ύ����
        110             db->QuerySql(COMMIT);
    111
        112             //2. ���������Ӧһ��Ӧ�� ��Ҫʱjson��ʽ
        113             response_json["is_insert"] = true;
    114             resp.body = writer.write(response_json);
    115             resp.set_header("Content-Type", "application/json");
    116
});
117
121             UrlUtil::PraseBody(res.body, &parm);
122             Json::Value requese_json;
123             request_json["email"] = parm["email"];
124             requese_json["password"] = parm["password"];
125
126             //2. У���û������������
127             // 2.1 �������ʧ�ܣ�������������false
128             // 2.2 ���У��ɹ���ִ������ĵ�����
129             // ����Ĳ������裬��Ҫ��ע����н��в�ѯ�����ύ������������Ϊ��ѯ������
130             // ������䲻���ڣ����½ʧ��
131             // ���������ڣ�������ȷ�����½�ɹ�������������¼ʧ��
132             Json::Value response_json;
133             bool ret = db_->QueryUserExist(request_json, &response_json);
134             if (!ret) {
    135                 response_json["login_status"] = false;
    136
}
137             else {
    138                 response_json["login_status"] = true;
    139
}
140
141             //3. ǰ�����ڵ�½�����������
142             //����sessionid ���û���ʶ��ǰ�û�
143
144             Json::FastWriter writer;
145             resp.body = writer.write(response_json);
146
147             resp.set_header("Content-Type", "application/json");
148             });
149         //��¼����
150         //����ԤԼ����
151         //�ύ����ԤԼ��������
152         //��������
153         http_svr_.set_mount_point("/", "./www");
155         http_svr_.listen(svr_ip_.c_str(), svr_port_);
156     }
157
158     bool Load(const std::string & config_filename) {//�����ļ����߼�
    160         if (!file.is_open()) {//�ж��Ƿ��
        161             LOG(ERROR, "open file failed") << std::endl;
        162             return false;//û�򿪷���false
        163
    }
    164
        165         //�������ļ���
        166         std::string line;//����string
    167         std::vector<std::string> output;//��������ÿһ�ж��������ݱ�������
    168         while (std::getline(file, line)) {//��ȡһ�����ݣ��������ݣ�ѭ����ȡ ��
        169             output.clear();
        170             StringTools::Split(line, "=", &output);
        171
            172             //��������
            173             if (strcmp(output[0].c_str(), "svr_ip") == 0) {
            174                 if (output[1].empty()) {
                175                     LOG(ERROR, "ip if empty") << std::endl;
                176                     return false;
                177
            }
            178                 svr_ip_ = output[1];
            179
        }
        180             else if (strcmp(output[0].c_str(), "svr_port") == 0) {
            181                 if (output[1].empty()) {
                182                     LOG(ERROR, "port is empty") << std::endl;
                183                     return false;
                184
            }
            185                 svr_port_ = atoi(output[1].c_str());
            186
        }
        187             else if (strcmp(output[0].c_str(), "db_ip") == 0) {
            188                 if (output[1].empty()) {
                189                     LOG(ERROR, "db_ip is empty") << std::endl;
                190                     return false;
                191
            }
            192                 db_ip_ = output[1];
            193
        }
        194             else if (strcmp(output[0].c_str(), "db_user") == 0) {
            195                 if (output[1].empty()) {
                196                     LOG(ERROR, "db_user is empty") << std::endl;
                197                     return false;
                198
            }
            199                 db_user_ = output[1];
            200
        }
        201             else if (strcmp(output[0].c_str(), "db_passwd") == 0) {
            202                 if (output[1].empty()) {
                203                     LOG(ERROR, "db_passwd is empty") << std::endl;
                204                     return false;
                205
            }
            206                 db_passwd_ = output[1];
            207
        }
        208             else if (strcmp(output[0].c_str(), "db_name") == 0) {
            209                 if (output[1].empty()) {
                210                     LOG(ERROR, "db_name is empty") << std::endl;
                211                     return false;
                212
            }
            213                 db_name_ output[1];
            214
        }
        215             else if (strcmp(output[0].c_str(), "db_port") == 0) {
            216                 if (output[1].empty()) {
                217                     LOG(ERROR, "db_user is empty") << std::endl;
                218                     return false;
                219
            }
            220                 db_port_ = atoi(output[1].c_str());
            221
        }
        222
    }
    223         return true;
    224
}
225 private:
    226     std::string svr_ip_;//�����������ip��ַ
    227     uint16_t svr_port_;//����������Ķ˿�
    228
        229     DateBaseSvr * db_;
    230     std::string db_ip_;
    231     std::string db_user_;
    232     std::string db_passwd_;
    233     std::string db_name_;
    234     uint16_t db_port_;
    235
        236     httplib::Server http_svr_;
    237 };
    238
        239
        240 int main() {
        241     AisSvr as;
        int ret = as.OnInit("./config_ais.cfg");
        if (ret < 0) {
            LOG(ERROR, "Init server failed") << std::endl;
            return -1;
        }
        as.Start();

        return 0;
    }






}
