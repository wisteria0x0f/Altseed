﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Reflection;
using FilePackageGenerator.Packaging;

namespace FilePackageGenerator
{
	public static class Program
	{
		static bool haveCurrentValue;

		static string GetVersionInfo()
		{
			Assembly thisAssembly = Assembly.GetExecutingAssembly();
			return "バージョン情報\n" + thisAssembly.ToString();
		}
		static string GetHelpInfo()
		{
			return @"
ディレクトリを指定して、その中にあるファイルをパッキングします。注意点として、パックファイルの中では大文字と小文字を区別しないため、大文字と小文字を区別するOSで使う場合には注意が必要となります。

FilePackagingTool [対象ディレクトリパス] [パックファイル名] [/m[[:]検索モード]] [/k [暗号キー]] [/n [パッキングしたくないファイルパス]]

 /m			指定した検索モードで探索を行います（省略可）

 検索モード		a すべてのファイル	nh 隠しファイル（フォルダ）を除く

 /k	暗号キー		暗号キーを設定して暗号をかけます（省略可）

 /n	ファイルパス	このパックファイルを基準にして指定したファイルパスを、これより優先度の低いルートから読み取らせないようにします
			複数入力可能です
";
		}
		static string GetTargetPath(IEnumerator<string> args)
		{
			if (haveCurrentValue)
			{
				string value = args.Current;
				haveCurrentValue = args.MoveNext();
				return value;
			}
			else
			{
				throw new ArgumentException("パックしたいディレクトリを設定してください");
			}
		}
		static string GetPackFileName(IEnumerator<string> args)
		{
			if (haveCurrentValue)
			{
				string value = args.Current;
				haveCurrentValue = args.MoveNext();
				return value;
			}
			else
			{
				throw new ArgumentException("パックファイルの名前を設定してください");
			}
		}
		static FilePackageGenerator.Packaging.PackagingSetting GetPackagingSetting(IEnumerator<string> args)
		{
			if (haveCurrentValue)
			{
				switch (args.Current)
				{
					case "/m:a":
						haveCurrentValue = args.MoveNext();
						return PackagingSetting.AllFiles;
					case "/m:nh":
						haveCurrentValue = args.MoveNext();
						return PackagingSetting.IgnoreHiddenAttribute;
					default:
						return PackagingSetting.IgnoreHiddenAttribute;
				}
			}
			else
				return PackagingSetting.IgnoreHiddenAttribute;
		}
		static string GetEncryptKey(IEnumerator<string> args)
		{
			if (haveCurrentValue)
			{
				switch (args.Current)
				{
					case "/k":
						if (!args.MoveNext())
							throw new ArgumentException("/k のあとに暗号キーのもとになるものが見つかりません");
						else
						{
							var value = args.Current;
							haveCurrentValue = args.MoveNext();
							return value;
						}
					default:
						return "";
				}
			}
			else
			{
				return "";
			}
		}
		static IEnumerable<string> GetIgnoreFilePath(IEnumerator<string> args)
		{
			if (haveCurrentValue)
			{
				switch (args.Current)
				{
					case "/f":
						if (!args.MoveNext())
							throw new ArgumentException("/f のあとに無視ファイル列挙パスが見つかりません");
						else
						{
							do
							{
								using (var reader = new System.IO.StreamReader(args.Current))
								{
									while (!reader.EndOfStream)
									{
										yield return reader.ReadLine();
									}
								}
							} while (args.MoveNext());

							haveCurrentValue = false;
						}
						break;
					default:
						do
						{
							yield return args.Current;
						} while (args.MoveNext());

						haveCurrentValue = false;

						break;
				}
			}
			else
			{
				yield return null;
			}
		}
		static IEnumerator<string> GetEnumrator(string[] args)
		{
			foreach (var str in args)
				yield return str;
		}
		public static string MainProgram(string[] args)
		{
			if (args.Length == 0)
				return GetHelpInfo();

			switch (args[0])
			{
				case "/h":
					return GetHelpInfo();
				case "/v":
					return GetVersionInfo();
				default:
					using (var enumerator = GetEnumrator(args))
					{
						haveCurrentValue = enumerator.MoveNext();

						var target = GetTargetPath(enumerator);
						var packName = GetPackFileName(enumerator);
						var setting = GetPackagingSetting(enumerator);
						var key = GetEncryptKey(enumerator);
						var ignore = GetIgnoreFilePath(enumerator).ToList();

						Packing.Run(target, packName, setting, ignore, key);
					}
					break;
			}

			return "パッキング終了";
		}
		static void Main(string[] args)
		{
			Console.WriteLine(MainProgram(args));
		}
	}
}
