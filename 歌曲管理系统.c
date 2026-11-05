#include <stdio.h>
#include <string.h>


struct Song {
	char song[50];
	char singer[30];
	int duration;
	int isFavorite; 
};


int saveSongs(struct Song songs[], int count);
int loadSongs(struct Song songs[], int n);
void deleteSong(struct Song songs[], int *count, int index);
void findSong(struct Song songs[], int count, char target[]);
int findSongIndex(struct Song songs[], int count, char target[]);
void showSongs(struct Song songs[], int count);
int modifySong(struct Song songs[], int count, int index);
int sortByDuration(struct Song songs[], int count, int order);
int sortByName(struct Song songs[], int count, int order);
void showStatistics(struct Song songs[], int count);
void toggleFavorite(struct Song songs[], int count, int index, int choice);
void showFavorites(struct Song songs[], int count);


int main() {
	int choice = 0;
	int count = 0; 
	
	struct Song songs[100];
	
	count = loadSongs(songs, 100);

	if (count == -1) {
	    count = 0;
	    printf("文件读取失败！将以空曲库启动。\n");
	}
	
	
	do {
	
		printf("\n===== 歌曲管理系统 =====\n");
		printf("1. 显示歌曲\n");
		printf("2. 保存歌曲\n");
		printf("3. 读取歌曲\n");
		printf("4. 删除歌曲（歌名）\n");
		printf("5. 删除歌曲（序号）\n"); 
		printf("6. 查找歌曲\n");
		printf("7. 修改歌曲信息\n");
		printf("8. 按时长排序\n");
		printf("9. 按歌名排序\n");
		printf("10. 歌曲统计\n");
		printf("11. 收藏/取消收藏\n");
		printf("12. 查看收藏歌曲\n");
		printf("0. 程序退出\n");
		
		printf("请选择：");
		if (scanf("%d", &choice) != 1) {
		    int ch;
		    while ((ch = getchar()) != '\n' && ch != EOF) {
		        ;
		    }
		
		    printf("\n输入出错！请重新输入。\n");
		    choice = -1; 
			continue;
		}
			
		switch (choice) {
			case 1: {
				printf("\n"); 
				if (count == 0) {
					printf("曲库为空\n");
				} else {
					int i;
					for (i = 0; i < count; i++) {
						printf("%s %s %d\n", 
								songs[i].song,
								songs[i].singer,
								songs[i].duration);
					}
					printf("\n一共有 %d 首歌曲\n", count);
				}
				printf("\n"); 
				break;
			}
			case 2: {
				printf("\n"); 
				printf("请输入歌曲信息\n");
				
				int temp = count;
				
				int answer = 1;
				while (count < 100 && answer == 1) {
					printf("\n歌曲名称 歌手 时长：\n");
					if (scanf("%49s %29s %d",
						songs[count].song,
						songs[count].singer,
						&songs[count].duration) == 3) {
						songs[count].isFavorite = 0;
						count++;
						printf("\n");
						printf("是否继续录入？（1继续，0结束）：");
						
						if (scanf("%d", &answer) != 1) {
							int ch;
						    while ((ch = getchar()) != '\n' && ch != EOF) {
						        ;
						    }
						    printf("输入错误，结束本次添加。\n");
						    break;
						} 
						if (answer != 0 && answer != 1) {
							printf("选项无效，结束本次添加。\n");
							break;
						}
						printf("\n");
					} else {
						int ch;
					    while ((ch = getchar()) != '\n' && ch != EOF) {
					        ;
					    }
					    
					    printf("输入格式错误！结束本次添加。\n");
					    break;
					}
					
				}
				
				if (count == 100) {
					printf("曲库已满！\n");
				}
				
				int result = saveSongs(songs, count);
				
				if (result == -1) {
					printf("保存失败！\n");
				} else {
					printf("\n本次新增了 %d 首歌曲！\n", result - temp);
				}
				printf("\n"); 
				break;
			}
			case 3: {
				printf("\n"); 
				int result = loadSongs(songs, 100);
				
				if (result == -1) {
					printf("读取失败！\n");
				} else {
					count = result;					
					printf("一共读取 %d 首歌曲\n", result);
				}
				printf("\n"); 
				break;
			}
			case 4: {
				printf("\n"); 
				char target[50];
				printf("注意：当含有重复时，此方式只能删除序号靠前的一个\n\n");
				printf("请输入要删除的歌曲名称：");
				if (scanf("%49s", target) != 1) {
					int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
				    printf("输入格式错误！结束本次删除。\n");
				    break;
				}
				
				int index = findSongIndex(songs, count, target);
				
				if (index == -1) {
					printf("未查询到相关结果，无法执行删除！\n");
				} else {
					
					deleteSong(songs, &count, index);
					
					int deleteResult = saveSongs(songs, count);
					if (deleteResult == -1) {
						printf("歌曲已从当前曲库删除，但保存失败！\n");
					} else {
						printf("歌曲删除并保存成功！\n");
					}
				printf("\n"); 	
				}
				break;
			}
			case 5: {
				printf("\n"); 
				if (count == 0) {
			        printf("曲库为空，无法删除！\n");
			        break;
			    }
			
			    printf("\n===== 歌单 =====\n");
				showSongs(songs, count);
			
			    int number;
			    printf("请输入要删除的歌曲序号：");
			    if (scanf("%d", &number) != 1) {
			    	int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
				    printf("\n输入格式错误！结束本次删除。\n");
				    break;
				}
			
			    if (number < 1 || number > count) {
			        printf("\n序号无效！\n");
			    } else {
			        int index = number - 1;
			
			        deleteSong(songs, &count, index);
			
			        int deleteResult = saveSongs(songs, count);
			
			        if (deleteResult == -1) {
			            printf("\n歌曲已从当前曲库删除，但保存失败！\n");
			        } else {
			            printf("\n歌曲删除并保存成功！\n");
			        }
			    }
			    printf("\n"); 
				break;
			}
			case 6: {
				printf("\n"); 
				if (count == 0) {
					printf("曲库为空，无法查询！\n");
				} else {
					
					char target[50];
					printf("请输入想要查询的歌名：");
					if (scanf("%49s", target) != 1) {
						int ch;
					    while ((ch = getchar()) != '\n' && ch != EOF) {
					        ;
					    }
					    
					    printf("输入错误，结束本次查询。\n");
					    break;
					}
					
					printf("\n查询结果：\n");
					findSong(songs, count, target);
			
				}
				printf("\n"); 
				break;
			}
			case 7: {
				printf("\n"); 
				if (count == 0) {
					printf("曲库为空，无法执行修改！\n");
					break;
				} 
				showSongs(songs, count);
				printf("请输入想要更改的歌曲序号：");
				
				int number;
				if (scanf("%d", &number) != 1) {
					int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
				    printf("\n输入格式错误！结束本次修改。\n");
				    break;
				}
				
				int index = number - 1;
				int result = modifySong(songs, count, index); 
				
				if (result == 1) {
					int saveResult = saveSongs(songs, count);
					if (saveResult == -1) {
						printf("修改内容保存失败！\n");
					} else {
						printf("修改内容保存成功！\n");
					}
				} else {
					printf("未进行修改或修改失败！\n");
				}
				printf("\n"); 
				break;
			}
			case 8: {
				printf("\n"); 
				if (count == 0) {
					printf("曲库为空，无法执行排序！\n");
					break;
				} 
				
				printf("请选择排序方式（1升序 / 2降序）：");
				
				int order;
				if (scanf("%d", &order) != 1) {
					int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
				    printf("\n输入格式错误！结束本次排序。\n");
				    break;
				}
				
				if (order != 1 && order != 2) {
					printf("\n输入无效，结束本次操作。\n");
					break;
				}
				
				int sortResult = sortByDuration(songs, count, order);
				if (sortResult == 1) {
					int saveResult = saveSongs(songs, count);
					if (saveResult == -1) {
						printf("排序结果保存失败！\n");
					} else {
						printf("排序结果保存成功！\n");
					}
				} else {
					printf("排序失败，不执行保存！\n");
				}
				printf("\n"); 
				break;
			}
			case 9: {
				printf("\n"); 
				if (count == 0) {
					printf("曲库为空，无法执行排序！\n");
					break;
				} 
				
				printf("请选择排序方式（1升序 / 2降序）：");
				
				int order;
				if (scanf("%d", &order) != 1) {
					int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
				    printf("\n输入格式错误！结束本次排序。\n");
				    break;
				}
				
				if (order != 1 && order != 2) {
					printf("\n输入无效，结束本次操作。\n");
					break;
				}
				
				int sortResult = sortByName(songs, count, order);
				if (sortResult == 1) {
					int saveResult = saveSongs(songs, count);
					if (saveResult == -1) {
						printf("排序结果保存失败！\n");
					} else {
						printf("排序结果保存成功！\n");
					}
				} else {
					printf("排序失败，不执行保存！\n");
				}
				printf("\n"); 
				break;
			}
			case 10: {
				printf("\n");
				
				printf("===== 歌曲统计 =====\n");
				showStatistics(songs, count);
				
				printf("\n");
				
				break;
			}
			case 11: {
				printf("\n");
				
				if (count == 0) {
					printf("曲库为空，无法操作！\n");
					break;
				}
				
				showSongs(songs, count);
				
				int number;
				printf("请输入要收藏或取消收藏的歌曲序号："); 
				
				if (scanf("%d", &number) != 1) {
					int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
					printf("输入错误，结束本次操作。\n");
					break;
				}
				
				if (number < 1 || number > count) {
					printf("无效序号！\n");
					break;
				} 
				
				printf("\n请输入操作（1收藏 / 0取消收藏）："); 
				
				int loveChoice;
				if (scanf("%d", &loveChoice) != 1) {
					int ch;
				    while ((ch = getchar()) != '\n' && ch != EOF) {
				        ;
				    }
				    
					printf("\n输入错误，结束本次操作。\n");
					break;
				}
				
				if (loveChoice != 0 && loveChoice != 1) {
					printf("\n输入无效，结束本次操作。\n");
					break;
				}
				
				int index = number - 1;
				toggleFavorite(songs, count, index, loveChoice);
				
				int result = saveSongs(songs, count);
				
				if (result == -1) {
					printf("保存失败！\n");
				} else {
					printf("保存成功！\n");
				}
				printf("\n");  
				break;
			}
			case 12: {
				printf("\n");
				
				if (count == 0) {
					printf("曲库为空，无法展示！\n");
					break;
				}
				
				printf("===== 我的收藏 =====\n");
				showFavorites(songs, count);
				
				printf("\n");
				
				break;
			}
			case 0:
				printf("\n"); 
				printf("程序退出！\n");
				break;
			
			default:
				printf("\n无效选项！\n");
		}
		
	} while (choice != 0);
	
	return 0; 
}







int saveSongs(struct Song songs[], int n) {
	FILE *fp = fopen("C_Project.txt", "w");
	
	if (fp == NULL) {
		printf("文件打开失败！\n");
		return -1;
	}
	
	int i = 0;
	while (i < n && fprintf(fp, "%s\t%s\t%d\t%d\n", 
				songs[i].song, 
				songs[i].singer, 
				songs[i].duration,
				songs[i].isFavorite) >= 0) {
		i++;
	}
	
	int closeResult = fclose(fp);
	
	if (i < n || closeResult != 0) {
		return -1;
	}
	
	return i;
}

int loadSongs(struct Song songs[], int n) {
	FILE *fp = fopen("C_Project.txt", "r");
	
	if (fp == NULL) {
		printf("文件打开失败！\n");
		return -1;
	}
	
	int count = 0;
	int readResult;
	int isError = 0;
	while (count < n) {
		readResult = fscanf(fp, "%49s %29s %d %d",
				songs[count].song,
				songs[count].singer,
				&songs[count].duration,
				&songs[count].isFavorite);
		if (readResult == 4) {
			count++;
		} else if(readResult == EOF) {
			if (ferror(fp)) {
				isError = 1;
			}
			break;
		} else {
			isError = 1;
			break;
		}
	}
	
	int closeResult = fclose(fp);
	
	if (isError || closeResult != 0) {
		printf("\n文件读取异常！\n");
		return -1;
	}
	
	return count;
}

void deleteSong(struct Song songs[], int *count, int index) {
	if (*count <= 0) {
		printf("曲库为空，无法执行删除！\n");
		return;
	}
	
	if (index < 0 || index >= *count) {
		printf("歌曲不存在，无法执行删除！\n");
		return;
	}
	
	int i, temp = *count;
	for (i = index; i < temp - 1; i++) {
		songs[i] = songs[i + 1];
	}
	(*count)--;
} 

void findSong(struct Song songs[], int count, char target[]) {
	int i, isFound = 0;
	for (i = 0; i < count; i++) {
		if (strcmp(songs[i].song, target) == 0) {
			isFound = 1;
			printf("%d. %s\t%s\t%d\n", i + 1, 
					songs[i].song,
					songs[i].singer,
					songs[i].duration);
		}
	}
	if (isFound == 0) {
		printf("未查询到相关结果！\n");
	}
}

int findSongIndex(struct Song songs[], int count, char target[]) {
	int i;
	for (i = 0; i < count; i++) {
		if (strcmp(songs[i].song, target) == 0) {
			return i;
		}
	}
	
	return -1;
}

void showSongs(struct Song songs[], int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf("%d. %s %s %d\n", 
			i + 1, 
			songs[i].song,
			songs[i].singer,
			songs[i].duration);
	}
}

int modifySong(struct Song songs[], int count, int index) {
	int isModified = 0;
	
	if (index < 0 || index >= count) {
		printf("无效序号！\n");
	} else {
		printf("\n%d. %s %s %d\n", index + 1, 
					songs[index].song, 
					songs[index].singer,
					songs[index].duration);
		int modifyChoice;
		do {
			printf("\n请选择更改内容（1歌名 / 2歌手 / 3时长 / 4退出）：");
			
			if (scanf("%d", &modifyChoice) != 1) {
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {
					;
				}
				
				printf("\n输入出错！正在返回菜单......\n");
				break;
			} 
			
			switch (modifyChoice) {
				case 1: {
					if (scanf("%49s", songs[index].song) == 1) {
						printf("修改成功！\n");
						isModified = 1;
					} else {
						int ch;
					    while ((ch = getchar()) != '\n' && ch != EOF) {
					        ;
					    }
					    
					    printf("\n输入错误，结束本次修改。\n");
					    return isModified;
					}
					break;
				}
				case 2: {
					if (scanf("%29s", songs[index].singer) == 1) {
						printf("\n修改成功！\n");
						isModified = 1;
					} else {
						int ch;
					    while ((ch = getchar()) != '\n' && ch != EOF) {
					        ;
					    }
					    
					    printf("\n输入错误，结束本次修改。\n");
					    return isModified;
					}
					break;
				}
				case 3: {
					if (scanf("%d", &songs[index].duration) == 1) {
						printf("\n修改成功！\n");
						isModified = 1;
					} else {
						int ch;
					    while ((ch = getchar()) != '\n' && ch != EOF) {
					        ;
					    }
					    
					    printf("\n输入错误，结束本次修改。\n");
					    return isModified;
					}
					break;
				}
				case 4: {
					printf("\n修改程序关闭！正在返回菜单......\n");
					break;
				} 
				default: 
					printf("\n无效选项！\n");
			} 
		} while (modifyChoice != 4);
		
	}
	
	return isModified;
}

int sortByDuration(struct Song songs[], int count, int order) {
	if (count == 0) {
		printf("\n曲库为空，无法排序！\n");
		return 0;
	}
	
	int i, j, swapped;
	
	struct Song temp;
	
	if (order == 1) {
		for (j = 0; j < count - 1; j++) {
			swapped = 0;
			for (i = 0; i < count - 1 - j; i++) {
				if (songs[i].duration > songs[i + 1].duration) {
					temp = songs[i];
					songs[i] = songs[i + 1];
					songs[i + 1] = temp;
					swapped = 1;
				}
			}
			if (swapped == 0) {
				break;
			}
		}
	} else if (order == 2) {
		for (j = 0; j < count - 1; j++) {
			swapped = 0;
			for (i = 0; i < count - 1 - j; i++) {
				if (songs[i].duration < songs[i + 1].duration) {
					temp = songs[i];
					songs[i] = songs[i + 1];
					songs[i + 1] = temp;
					swapped = 1;
				}
			}
			if (swapped == 0) {
				break;
			}
		}
	} else {
		printf("\n无效排序方式！\n");
		return 0;
	}
	
	printf("\n排序结束！\n");
	
	printf("\n");
	showSongs(songs, count);
	
	return 1;
}

int sortByName(struct Song songs[], int count, int order) {
	if (count == 0) {
		printf("\n曲库为空，无法排序！\n");
		return 0;
	}
	
	int i, j, swapped;
	
	struct Song temp;
	
	if (order == 1) {
		for (j = 0; j < count - 1; j++) {
			swapped = 0;
			for (i = 0; i < count - 1 - j; i++) {
				if (strcmp(songs[i].song, songs[i + 1].song) > 0) {
					temp = songs[i];
					songs[i] = songs[i + 1];
					songs[i + 1] = temp;
					swapped = 1;
				}
			}
			if (swapped == 0) {
				break;
			}
		}
	} else if (order == 2) {
		for (j = 0; j < count - 1; j++) {
			swapped = 0;
			for (i = 0; i < count - 1 - j; i++) {
				if (strcmp(songs[i].song, songs[i + 1].song) < 0) {
					temp = songs[i];
					songs[i] = songs[i + 1];
					songs[i + 1] = temp;
					swapped = 1;
				}
			}
			if (swapped == 0) {
				break;
			}
		}
	} else {
		printf("\n无效排序方式！\n");
		return 0;
	}
	
	printf("\n排序结束！\n");
	
	printf("\n");
	showSongs(songs, count);
	
	return 1;
}

void showStatistics(struct Song songs[], int count) {
	if (count == 0) {
		printf("曲库为空，无法进行统计！\n");
		return;
	}
	
	int i, sumNum = count, sumTime = 0;
	double average = 0.0;
	
	for (i = 0; i < count; i++) {
		sumTime += songs[i].duration;
	} 
	
	average = sumTime*1.0 / sumNum;
	
	printf("歌曲总数：%d\n", sumNum);
	printf("总时长：%d\n", sumTime);
	printf("平均时长：%.2f\n", average);
	
	return;
}

void toggleFavorite(struct Song songs[], int count, int index, int choice) {
	if (count == 0) {
		printf("曲库为空，无法操作！\n");
		return;
	}
	
	if (choice != 0 && choice != 1) {
	    printf("无效操作！\n");
	    return;
	}
	
	if (index < 0 || index >= count) {
		printf("无效序号！\n");
		return;
	} 
	
	if (choice == 1) {
		songs[index].isFavorite = 1;
		printf("歌曲已收藏！\n\n");
	} else {
		songs[index].isFavorite = 0;
		printf("歌曲已取消收藏！\n\n");
	}
	
	return;
}

void showFavorites(struct Song songs[], int count) {
	if (count == 0) {
		printf("曲库为空，无法查看！\n");
		return;
	}
	
	int i, cnt = 0;
	for (i = 0; i < count; i++) {
		if (songs[i].isFavorite) {
			printf("%d. %s %s %d\n", 
				i + 1,
				songs[i].song,
				songs[i].singer,
				songs[i].duration);
			cnt++;
		}
	} 
	
	if (cnt == 0) {
		printf("暂无收藏歌曲！\n");
	} else {
		printf("一共收藏了 %d 首歌曲！\n", cnt);
	}
	
	return;
}
