DELIMITER $$

DROP PROCEDURE IF EXISTS `combine`$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `combine`(IN fromdbs VARCHAR(200),IN todb VARCHAR(30))
BEGIN
DECLARE dsize INT DEFAULT 0;
DECLARE lastLoginId BIGINT DEFAULT -1;
DECLARE currentUUID BIGINT DEFAULT -1;
DECLARE currentLoginId BIGINT DEFAULT -1;
DECLARE done INT DEFAULT FALSE;
-- 遍历playercache 通过 loginId,lv,gsPoint,uuid降序
DECLARE cur1 CURSOR FOR SELECT `uuid`,loginid FROM playercache  ORDER BY loginId DESC, lv DESC,gsPoint DESC,`uuid` DESC;
-- 遍历废弃玩家，条件是 等级小于20 ，30天类没有升级
DECLARE cur2 CURSOR FOR SELECT `uuid` FROM playercache WHERE lv<20 AND (UNIX_TIMESTAMP(NOW())-(lvUpTime/1000))>30*24*60*60;
-- 遍历有效玩家
DECLARE cur3 CURSOR FOR SELECT `uuid` FROM playercache;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
SET @needDeletes ='';
SET @count=CHAR_LENGTH(fromdbs)-CHAR_LENGTH(REPLACE(fromdbs,',','')) + 1;
SET @i=1;
ALTER TABLE pay MODIFY id BIGINT;
WHILE @i <= @count
DO
SET @fromdb=SUBSTRING_INDEX(SUBSTRING_INDEX(fromdbs,',',@i),',',-1);
SET @tail=SUBSTRING(@fromdb,5);
#合并bags表
SET @sql_bags=CONCAT('INSERT INTO ',todb,'.bags SELECT * FROM ',@fromdb,'.bags');
PREPARE pre_bags FROM @sql_bags;
EXECUTE pre_bags;
DEALLOCATE PREPARE pre_bags;
-- 合并friends表
SET @sql_friends=CONCAT('INSERT INTO ',todb,'.friends SELECT * FROM ',@fromdb,'.friends');
PREPARE pre_friends FROM @sql_friends;
EXECUTE pre_friends;
DEALLOCATE PREPARE pre_friends;
-- 合并heros表
SET @sql_heros=CONCAT('INSERT INTO ',todb,'.heros SELECT * FROM ',@fromdb,'.heros');
PREPARE pre_heros FROM @sql_heros;
EXECUTE pre_heros;
DEALLOCATE PREPARE pre_heros;
#合并mails表
SET @sql_mails=CONCAT('INSERT INTO ',todb,'.mails SELECT * FROM ',@fromdb,'.mails');
PREPARE pre_mails FROM @sql_mails;
EXECUTE pre_mails;
DEALLOCATE PREPARE pre_mails;
#合并offlines表
SET @sql_offlines=CONCAT('INSERT INTO ',todb,'.offlines SELECT * FROM ',@fromdb,'.offlines');
PREPARE pre_offlines FROM @sql_offlines;
EXECUTE pre_offlines;
DEALLOCATE PREPARE pre_offlines;
#合并pay表
SET @sql_pay=CONCAT('INSERT INTO ',todb,'.pay SELECT A.uuid,B.loginId,B.moneys FROM ',@fromdb,'.playercache A,',@fromdb,'.pay B WHERE A.loginId=B.loginId');
PREPARE pre_pay FROM @sql_pay;
EXECUTE pre_pay;
DEALLOCATE PREPARE pre_pay;
#合并player表
SET @sql_player=CONCAT('INSERT INTO ',todb,'.player SELECT * FROM ',@fromdb,'.player');
PREPARE pre_player FROM @sql_player;
EXECUTE pre_player;
DEALLOCATE PREPARE pre_player;
#合并playercache表
SET @sql_playercache=CONCAT('INSERT INTO ',todb,'.playercache SELECT * FROM ',@fromdb,'.playercache where loginId>0');
PREPARE pre_playercache FROM @sql_playercache;
EXECUTE pre_playercache;
DEALLOCATE PREPARE pre_playercache;
#合并rewardmission表
SET @sql_rewardmission=CONCAT('INSERT INTO ',todb,'.rewardmission SELECT * FROM ',@fromdb,'.rewardmission');
PREPARE pre_rewardmission FROM @sql_rewardmission;
EXECUTE pre_rewardmission;
DEALLOCATE PREPARE pre_rewardmission;
#合并tasks表
SET @sql_tasks=CONCAT('INSERT INTO ',todb,'.tasks SELECT * FROM ',@fromdb,'.tasks');
PREPARE pre_tasks FROM @sql_tasks;
EXECUTE pre_tasks;
DEALLOCATE PREPARE pre_tasks;
#合并tongs表
SET @sql_tongs=CONCAT('INSERT INTO ',todb,'.tongs SELECT CONCAT(',@tail,',tongId,"") tongId ,tong FROM ',@fromdb,'.tongs');
PREPARE pre_tongs FROM @sql_tongs;
EXECUTE pre_tongs;
DEALLOCATE PREPARE pre_tongs;
#设置数据库下标，继续下一个数据库的合并
SET @i=@i+1;
END WHILE;
 
#一个玩家多个角色只保留一个角色,保留等级高的,战力高的
OPEN cur1;
loop1: LOOP
FETCH cur1 INTO currentUUID,currentLoginId;
IF done THEN
LEAVE loop1;
END IF;
IF (currentLoginId=lastLoginId) THEN
SET @needDeletes=CONCAT(@needDeletes,',',currentUUID);
SET dsize =dsize+1;
ELSE  
SET lastLoginId=currentLoginId;
END IF;
END LOOP;
CLOSE cur1; 
IF (dsize>0) THEN
SET @needDeletes=SUBSTRING(@needDeletes,2);
#删除废弃的playercache数据
SET @del_sql_playercache =CONCAT('UPDATE playercache SET STATUS=1 WHERE `uuid` IN (',@needDeletes,')');
PREPARE del_playercache FROM @del_sql_playercache;
EXECUTE del_playercache;
DEALLOCATE PREPARE del_playercache;
#删除废弃的pay数据
SET @del_sql_pay =CONCAT('DELETE FROM pay WHERE id  IN (',@needDeletes,')');
PREPARE del_pay FROM @del_sql_pay;
EXECUTE del_pay;
DEALLOCATE PREPARE del_pay;
SET @needDeletes='';
SET dsize =0;
END IF;
-- 删除低等级很多天没登录的玩家数据
SET done=FALSE;
OPEN cur2;
loop2: LOOP
FETCH cur2 INTO currentUUID;
IF done THEN
LEAVE loop2;
END IF;
SET @needDeletes=CONCAT(@needDeletes,',',currentUUID);
SET dsize =dsize+1;
END LOOP;
CLOSE cur2;
IF (dsize>0) THEN
SET @needDeletes=SUBSTRING(@needDeletes,2);
#删除废弃的playercache数据
SET @del_sql_playercache =CONCAT('DELETE FROM playercache WHERE `uuid` IN (',@needDeletes,')');
PREPARE del_playercache FROM @del_sql_playercache;
EXECUTE del_playercache;
DEALLOCATE PREPARE del_playercache;
SET @needDeletes='';
SET dsize =0;
END IF;
SET done=FALSE;
OPEN cur3;
loop3: LOOP
FETCH cur3 INTO currentUUID;
IF done THEN
LEAVE loop3;
END IF;
SET @needDeletes=CONCAT(@needDeletes,',',currentUUID);
SET dsize =dsize+1;
END LOOP;
CLOSE cur3;
IF (dsize>0) THEN
SET @needDeletes=SUBSTRING(@needDeletes,2);
#删除废弃的bags数据
SET @del_sql_bags =CONCAT('DELETE FROM bags WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_bags FROM @del_sql_bags;
EXECUTE del_bags;
DEALLOCATE PREPARE del_bags;

#删除废弃的friends数据
SET @del_sql_friends =CONCAT('DELETE FROM friends WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_friends FROM @del_sql_friends;
EXECUTE del_friends;
DEALLOCATE PREPARE del_friends;

#删除废弃的heros数据
SET @del_sql_heros =CONCAT('DELETE FROM heros WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_heros FROM @del_sql_heros;
EXECUTE del_heros;
DEALLOCATE PREPARE del_heros;

#删除废弃的mails数据
SET @del_sql_mails =CONCAT('DELETE FROM mails WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_mails FROM @del_sql_mails;
EXECUTE del_mails;
DEALLOCATE PREPARE del_mails;

#删除废弃的offlines数据
SET @del_sql_offlines =CONCAT('DELETE FROM offlines WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_offlines FROM @del_sql_offlines;
EXECUTE del_offlines;
DEALLOCATE PREPARE del_offlines;

#删除废弃的pay数据
SET @del_sql_pay =CONCAT('DELETE FROM pay WHERE id NOT IN (',@needDeletes,')');
PREPARE del_pay FROM @del_sql_pay;
EXECUTE del_pay;
DEALLOCATE PREPARE del_pay;

#删除废弃的player数据
SET @del_sql_player =CONCAT('DELETE FROM player WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_player FROM @del_sql_player;
EXECUTE del_player;
DEALLOCATE PREPARE del_player;

#删除废弃的rewardmission数据
SET @del_sql_rewardmission =CONCAT('DELETE FROM rewardmission WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_rewardmission FROM @del_sql_rewardmission;
EXECUTE del_rewardmission;
DEALLOCATE PREPARE del_rewardmission;

#删除废弃的tasks数据
SET @del_sql_tasks =CONCAT('DELETE FROM tasks WHERE `uuid` NOT IN (',@needDeletes,')');
PREPARE del_tasks FROM @del_sql_tasks;
EXECUTE del_tasks;
DEALLOCATE PREPARE del_tasks;

SET @needDeletes='';
SET dsize =0; 
END IF;
-- 重名数据处理
UPDATE playercache E,(SELECT A.uuid,A.name,@no:=@no+1 nbr  FROM playercache A,(SELECT @no:=0)C,(SELECT NAME,MIN(createtime) createtime,COUNT(NAME) num FROM playercache 
GROUP BY NAME HAVING COUNT(num)>1)B WHERE A.name=B.name AND A.createtime>B.createtime) F SET E.name=CONCAT(F.name,F.nbr,'@') WHERE E.uuid =F.uuid;

-- 将pay的id 变成 int类型
UPDATE pay D, (SELECT (@num:=@num+1) num,id FROM pay A,(SELECT @num:=0) B) C SET D.id =C.num WHERE D.id=C.id;

ALTER TABLE pay MODIFY id INT;
END$$
DELIMITER ; 