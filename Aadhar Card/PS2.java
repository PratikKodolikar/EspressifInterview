package espressif;

import java.sql.*;
import java.util.Scanner;

public class PS2 {

    public static void main(String[] args) {
        String id;
        int choice;
        String i;
        Scanner s = new Scanner(System.in);
        functions p = new functions();
        p.display(1);
        do {

            System.out.println("\nEnter\n1. add a new record\n2. delete any record\n3. Search a record by name" +
                    "\n4. Search a record by id\n5. Update a record\n6. display database " +
                    "\n7. to check if a record is blacklisted\n8. to blacklist a record\n9. to display blacklist contacts" +
                    "\n10. to remove from blacklist");
            choice = s.nextInt();
            switch (choice) {
                case 1:
                    p.display(1);
                    System.out.println("enter name to insert (first middle last)");
                    p.getname();
                    System.out.println("enter Aadhar id");
                    id = s.next();
                    p.insert(id);
                    break;
                case 2:

                    p.display(1);
                    System.out.println("enter name(first middle last) to delete");
                    p.getname();
                    p.delete();
                    p.display(1);
                    break;
                case 3:
                    System.out.println("Enter the name to search");
                    p.getname();
                    p.Search("NULL");
                    break;
                case 4:
                    System.out.println("Enter the aadhar id to search");
                    id = s.next();
                    p.Search(id);
                    break;
                case 5:
                    System.out.println("Enter the id to update");
                    int Id = s.nextInt();
                    p.update(Id);
                    p.display(1);
                    break;
                case 6:
                    p.display(1);
                    break;
                case 7:
                    p.display(0);
                    System.out.println("Enter the name to check if it's blacklisted");
                    p.getname();
                    p.is_Blacklist();
                    break;
                case 8:
                    System.out.println("Enter name to black list");
                    p.getname();
                    p.to_blacklist();
                    p.display(1);
                    break;
                case 9:
                    System.out.println("Enter root password to display blacklist records to: ");
                    String root = s.next();
                    if (root.equals("root"))
                        p.display(0);
                    else {
                        System.out.println("incorrect password");
                        p.display(1);
                    }
                    break;
                case 10:
                    p.display(0);
                    System.out.println("Enter name to remove from black list");
                    p.getname();
                    p.remove_blacklist();
                    p.display(1);
                    break;

                default:
                    System.out.println("Enter valid option");
            }

            System.out.println("Do you wish to continue (Y/N)");
            i = s.next();
            i = i.toLowerCase();

        } while (i.equals("y"));

    }

}


class functions {
    private Statement stat;
    private String Fname, Mname, Lname;


    private int check_id(String id) {//to check if the input aadhar id is correct
        if (id.matches("[0-9]+") && id.length() == 12) {
            return 1;
        } else {
            return 0;
        }
    }


    protected void getname() {// function to obtain the name from the user
        Fname = null;
        Mname = null;
        Lname = null;
        Scanner s = new Scanner(System.in);
        String[] name = s.nextLine().split(" ");
        try {
            Fname = name[0];
            Mname = name[1];
            Lname = name[2];
        } catch (ArrayIndexOutOfBoundsException ignored) {
        }
    }

    public functions() {//constructor to connect to the database
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        String DB_URL = "jdbc:mysql://localhost:3306/aadhar_card_management";
        String uname = "root";
        String pword = "root";
        try {
            Connection con = DriverManager.getConnection(DB_URL, uname, pword);
            stat = con.createStatement();
        } catch (Exception err) {
            err.printStackTrace();
        }
    }

    public void display(int flag) {// to display the records
        System.out.println("The DATABASE is :-");
        try {
            ResultSet rs;
            String sql;
            if (flag == 1) {
                sql = "select * from aadhar_card  WHERE blacklisted = 'no'";
            } else {
                sql = "select * from aadhar_card ";
            }
            rs = stat.executeQuery(sql);
            int i = 1;
            while (rs.next()) {
                String a_id = rs.getString("aadhar_id");
                String first_name = rs.getString("First_Name");
                String middle_name = rs.getString("Guardian_Name");
                String last_name = rs.getString("Last_Name");

                String p = i + " " + a_id + " " + first_name + " " + middle_name + " " + last_name;
                System.out.println(p);
                i++;
            }

        } catch (Exception err) {
            System.out.println(err.getMessage());
        }
    }

    private int set_serial_id(){ // returns serial id for the inserted record
        String sql = "select * from aadhar_card ";
        int i = 1;
        try
        {
            ResultSet rs = stat.executeQuery(sql);

            while (rs.next()) {
                i++;
            }

        }catch (Exception err) {
            System.out.println(err.getMessage());
        }
        return i;
    }
    public void insert(String Aadhar_id) { // insert a new record
        int i = set_serial_id();
        if (check_id(Aadhar_id) == 1) {
            String sql = "INSERT INTO `aadhar_card_management`.`aadhar_card` (`id`, `aadhar_id`, `First_name`, `Guardian_name`, `Last_name`, `blacklisted`) VALUES";
            String insert = "('"+i+"', '" + Aadhar_id + "', '" + Fname + "', '" + Mname + "', '" + Lname + "','no')";
            try {
                stat.executeUpdate((sql + insert));
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("Enter valid aadhar number");
        }
    }

    public void delete() {// delete a record by full name
        String sql = "DELETE FROM aadhar_card WHERE First_Name = '" + Fname + "' AND Guardian_Name = '" + Mname + "' AND Last_Name = '" + Lname + "'";
        try {
            stat.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void Search(String id) { // to search and display the record using aadhar id or name
        if (id.compareTo("NULL") != 0 && check_id(id)==1) {
            String sql = " SELECT * FROM aadhar_card WHERE aadhar_id = " + id;

            try {
                ResultSet rs = stat.executeQuery(sql);
                while (rs.next()) {
                    int id_col = rs.getInt("id");
                    String a_id = rs.getString("aadhar_id");
                    String first_name = rs.getString("First_Name");
                    String last_name = rs.getString("Guardian_Name");
                    String job = rs.getString("Last_Name");

                    String p = id_col + " " + a_id + " " + first_name + " " + last_name + " " + job;
                    System.out.println(p);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else {
            String sql = " SELECT * FROM aadhar_card WHERE First_Name LIKE \"%" + Fname + "%\" OR Guardian_Name LIKE \"%" + Mname + "%\" OR Last_Name LIKE \"%" + Lname + "%\"";
            try {
                ResultSet rs = stat.executeQuery(sql);
                while (rs.next()) {
                    int id_col = rs.getInt("id");
                    String a_id = rs.getString("aadhar_id");
                    String first_name = rs.getString("First_Name");
                    String last_name = rs.getString("Guardian_Name");
                    String job = rs.getString("Last_Name");

                    String p = id_col + " " + a_id + " " + first_name + " " + last_name + " " + job;
                    System.out.println(p);

                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
                e.printStackTrace();
            }

        }
    }

    public void update(int id) { // update any field of the record except aadhar number
        String name, sql = "NULL";
        Scanner s = new Scanner(System.in);
        System.out.println("Enter field to update ");
        System.out.println("first_name\nmiddle_name\nlast_name");
        String choice = s.next();
        choice = choice.toLowerCase();
        switch (choice) {
            case "aadhar_id":
                System.out.println("Cannot update aadhar id");
                break;
            case "first_name":
                System.out.println("Enter first name");
                name = s.next();
                sql = "UPDATE aadhar_card SET First_name = '" + name + "' WHERE id = " + id;
                break;
            case "middle_name":
                System.out.println("Enter middle name");
                name = s.next();
                sql = "UPDATE aadhar_card SET Guardian_name = '" + name + "' WHERE id = " + id;
                break;
            case "last_name":
                System.out.println("Enter last name");
                name = s.next();
                sql = "UPDATE aadhar_card SET Last_name = '" + name + "' WHERE id = " + id;
                break;
            default:
                System.out.println("Enter valid option");
        }
        if (!sql.equals("NULL")) {
            try {
                stat.executeUpdate(sql);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("enter name");
        }
    }

    public void is_Blacklist() {// to check if its blacklist
        String sql = "SELECT blacklisted from aadhar_card WHERE First_Name LIKE \"%" + Fname + "%\" AND Guardian_Name LIKE \"%" + Mname + "%\" AND Last_Name LIKE \"%" + Lname + "%\"";
        try {
            String Blacklist = "";
            stat.executeQuery(sql);
            ResultSet rs = stat.executeQuery(sql);
            if (rs.next()) {
                Blacklist = rs.getString("blacklisted");
            }
            System.out.println(Blacklist);
            if (Blacklist.compareTo("no") == 0) {
                System.out.println("Its not Blacklisted");
            } else {
                System.out.println("It is Blacklisted");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }


    }

    public void to_blacklist() { // to blacklist a record
        String sql = " UPDATE aadhar_card SET blacklisted = 'yes' WHERE First_Name LIKE \"%" + Fname + "%\" AND Guardian_Name LIKE \"%" + Mname + "%\" AND Last_Name LIKE \"%" + Lname + "%\"";
        try {
            stat.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void remove_blacklist() { // to remove a record from blacklist
        String sql = null;
        sql = " UPDATE aadhar_card SET blacklisted = 'no' WHERE blacklisted = 'yes' AND First_Name LIKE \"%" + Fname + "%\" AND Guardian_Name LIKE \"%" + Mname + "%\" AND Last_Name LIKE \"%" + Lname + "%\"";
        if (sql.isEmpty()) System.out.println("it is not blacklisted");
        else {
            try {
                stat.executeUpdate(sql);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

    }
}
