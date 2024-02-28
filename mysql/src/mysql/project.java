package mysql;

import java.util.*;
import java.sql.*;

public class project {
	public static void main(String args[]) {
		Connection connection = null;
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			connection = DriverManager.getConnection("jdbc:mysql://10.10.15.233:3306/te31322db", "te31322", "te31322");
			Statement statement = connection.createStatement();
			// String print = "select * from Employee;";
			ResultSet result;
			Scanner sc = new Scanner(System.in);
			String ch = "y";
			while (ch != "n") {
				System.out.println("----------------------------------------------------------");
				System.out.println("1. Print Records");
				System.out.println("2. Add Records");
				System.out.println("3. Update Record");
				System.out.println("4. Delete Record");
				int c = sc.nextInt();
				if (c == 1) {
					String print = "select roll,name,salary from Employee;";
					result = statement.executeQuery(print);
					while (result.next()) {
						System.out.print(result.getInt(1));
						System.out.print(" ");
						System.out.print(result.getString(2));
						System.out.println("");
						System.out.print(result.getInt(3));
						System.out.println("");
					}
				} else if (c == 2) {
					String name;
					int salary, roll;
					System.out.println("Enter roll,name,salary of the Employee - ");
					roll = sc.nextInt();
					name = sc.next();
					salary = sc.nextInt();
					// String insert = "insert into values(" + roll + "," +" ' " + name + "');";
					// statement=connection.prepareStatement("insert into Employee values (?,?,?)");
					// statement.setInt(1,sc.nextInt(););
					// statement.setString(2,name);
					// statement.setInt(3,salary);
					// statement.executeUpdate();
					String insert = "insert into Employee values(" + roll + "," + " ' " + name + "'" + "," + "+"
							+ salary + ");";
					statement.executeUpdate(insert);
				} else if (c == 3) {
					String name;
					int roll;
					System.out.println("Enter roll of the employee who's record to be updated - ");
					roll = sc.nextInt();
					System.out.println("Enter new name - ");
					name = sc.next();
					String update = "update Employee set name = " + "'" + name + "'" + " where roll = " + roll + ";";
					statement.executeUpdate(update);
				} else if (c == 4) {
					// String name ;
					int roll;
					System.out.println("Enter roll  of the employee who's record to be deleted - ");
					roll = sc.nextInt();
					String del = "delete from Employee where roll = " + roll + ";";
					statement.executeUpdate(del);
				} else {
					System.out.println("You have entered a wrong choice.");
				}

				System.out.println("Do you want to continue (y/n) - ");
				ch = sc.next();
				if (ch == "n") {
					ch = "n";
				}
			}

		} catch (Exception e) {
			System.out.print(e);
		}
	}
}
