
// std::map<int ,std::shared_ptr<UserLogContext> > UserLogRecordMGR::m_contentlog_map;
// //获取content_log_t error code对应的数据
// std::shared_ptr<UserLogContext> UserLogRecordMGR::GetContentLogMsg(const int ErrorCode){
// //初始化成功 error code存在 find map 返回信息
// 	if(!IsUserLogNOExist(ErrorCode)){
// 		LOG(ERROR)<<"NO ERROR CODE IN CONTENT_LOG_T TABLE!!!";
// 		return NULL;
// 	}
// 	map<int,std::shared_ptr<UserLogContext>>::iterator iter =m_contentlog_map.find(ErrorCode);
// 	if(iter != m_contentlog_map.end()){
// 		return iter->second;
// 	}
// 	return NULL;
// }